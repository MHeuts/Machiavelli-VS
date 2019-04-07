#include "pch.h"
#include "thief_state.h"
#include "Game.h"

thief_state::thief_state() : thief_state(nullptr)
{
}

thief_state::thief_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void thief_state::enter_state()
{
	const auto game = Game::instance();
	game->current_client->render_screen();
	opponent = game->current_client == game->client1 ? game->client2 : game->client1;
}

void thief_state::leave_state()
{
	Game::instance()->current_client->set_message("You choose the " + character->name + " card.");

	auto opp_msg = "The Thief choose the " + character->name + " card.";
	if (stole_from_opponent)
	{
		opp_msg += Socket::endl + "Your " + character->name + " was pickpocketed by the thief, you lost all your gold.";
	}

	opponent->set_message(opp_msg);
}

void thief_state::render(std::shared_ptr<ClientInfo>& client)
{
	const auto game = Game::instance();

	client->send_header();

	if (client == Game::instance()->current_client)
	{
		client->get_socket() << "Choose a character card that you want to steal from." << Socket::endl << Socket::endl
			<< game->character_deck.print_original_cards()
			<< "(" << game->character_deck.get_original_cards().size() + 1
			<< ") Go Back." << Socket::endl << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to pick a card." << Socket::endl;
	}
}

void thief_state::handle_input(std::shared_ptr<ClientCommand>& command)
{
	const auto game = Game::instance();
	const auto client = command->get_client_info().lock();

	if (client != game->current_client) return;

	int action = -1;
	try
	{
		action = atoi(command->get_cmd().c_str());
	}
	catch (...) {}
	action--;

	if (action == game->character_deck.get_original_cards().size())
	{
		switch_state = true;
		return;
	}

	if (action < 0 || action >= game->character_deck.get_original_cards().size())
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	character = game->character_deck.get_original_cards().at(action);

	if (client->get_player().has_card(character))
	{
		client->set_message("DON'T STEAL FROM YOURSELF");
		return;
	}

	const auto found_card = opponent->get_player().has_card(character);

	if (character->name == "Thief" || character->name == "Assassin" || (found_card != nullptr && found_card->killed))
	{
		client->set_message("You cannot steal from yourself, the assassin or a dead character.");
		return;
	}

	if (found_card != nullptr)
	{
		found_card->robbed = true;
		stole_from_opponent = true;
	}

	client->get_player().get_turn().use_ability();

	switch_state = true;
}

void thief_state::update()
{
	if (switch_state)
	{
		Game::instance()->exit_current_state(old_state);
	}
}
