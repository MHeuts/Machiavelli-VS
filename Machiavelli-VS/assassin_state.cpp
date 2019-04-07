#include "pch.h"
#include "assassin_state.h"
#include "Game.h"
#include <algorithm>

assassin_state::assassin_state() : assassin_state(nullptr)
{
}

assassin_state::assassin_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void assassin_state::enter_state()
{
	const auto game = Game::instance();
	game->current_client->render_screen();

	opponent = game->current_client == game->client1 ? game->client2 : game->client1;
}

void assassin_state::leave_state()
{
	Game::instance()->current_client->set_message("You killed the " + character->name + ".");
	opponent->set_message((killed_opponent_card ? "Your " : "The ") + character->name + " has been killed.");
}

void assassin_state::render(std::shared_ptr<ClientInfo>& client)
{
	const auto game = Game::instance();
	client->send_header();

	if (client == game->current_client)
	{
		client->get_socket() << "Choose a character card that you want to kill." << Socket::endl << Socket::endl
			<< game->character_deck.print_original_cards()
			<< "(" << game->character_deck.get_original_cards().size() + 1 << ") Go Back."
			<< Socket::endl << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to pick a card." << Socket::endl;
	}
}

void assassin_state::handle_input(std::shared_ptr<ClientCommand>& command)
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

	if (action < 0 || action > game->character_deck.get_original_cards().size())
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	character = game->character_deck.get_original_cards().at(action);

	if (character->name == "Assassin")
	{
		client->set_message("You have killed yourself, smart boi");
		return;
	}

	const auto found_card = opponent->get_player().has_card(character);

	if (found_card != nullptr)
	{
		found_card->killed = true;
		killed_opponent_card = true;
	}

	client->get_player().get_turn().use_ability();

	switch_state = true;
}

void assassin_state::update()
{
	if (switch_state)
	{
		Game::instance()->exit_current_state(old_state);
	}
}
