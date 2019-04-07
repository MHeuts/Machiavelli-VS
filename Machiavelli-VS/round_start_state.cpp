#include "pch.h"
#include <random>
#include "round_start.h"
#include "Random.h"
#include "turn_state.h"

round_start_state::round_start_state() : round_start_state(nullptr)
{
}

round_start_state::round_start_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void round_start_state::enter_state()
{
	const auto game = Game::instance();

	// Reset cards
	game->current_card = nullptr;
	game->character_deck.reset();

	game->client1->get_player().character_cards.clear();
	game->client2->get_player().character_cards.clear();
	
	std::random_shuffle(game->character_deck.cards.begin(), game->character_deck.cards.end());

	// Assign king
	game->current_client = game->client1->get_player().is_king ? game->client1 : game->client2;

	if (game->round > 0)
	{
		game->client1->set_message("New round.");
		game->client2->set_message("New round.");

		game->current_client->set_message("You were the king last round, you may pick a card first.");
	}


	const int index = Random::instance().get(game->character_deck.cards.size() - 1);
	const auto character = game->character_deck.cards.at(index);
	game->current_client->set_message(character->name + " is removed");
	game->character_deck.cards.erase(game->character_deck.cards.begin() + index);

	// Render screens for players
	game->client1->render_screen();
	game->client2->render_screen();
}

void round_start_state::leave_state()
{
	const auto game = Game::instance();

	game->round++;

	game->client1->set_message("Round " + std::to_string(game->round));
	game->client2->set_message("Round " + std::to_string(game->round));
}

void round_start_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();

	if (client == Game::instance()->current_client)
	{
		if (!DiscardState) {
			client->get_socket() << "Please pick a card:" << Socket::endl
				<< Game::instance()->character_deck.to_string()
				<< Socket::endl;
		}
		else
		{
			client->get_socket() << "Please pick a card to discard:" << Socket::endl
				<< Game::instance()->character_deck.to_string()
				<< Socket::endl;
		}
	}
	else
	{
		client->get_socket() << "Please wait for the player to pick a card." << Socket::endl;
	}
}

void round_start_state::handle_input(std::shared_ptr<ClientCommand>& command)
{
	const auto game = Game::instance();
	const auto client = command->get_client_info().lock();
	if (client != game->current_client) return;

	int card = -1;
	try
	{
		card = atoi(command->get_cmd().c_str());
	}
	catch (...) {}

	card--;

	if (card < 0 || card > game->character_deck.cards.size() - 1)
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	if(!DiscardState)
	{
		const auto character = game->character_deck.cards.at(card);
		client->get_player().character_cards.push_back(character);
		game->character_deck.cards.erase(std::remove(game->character_deck.cards.begin(), game->character_deck.cards.end(), character));

		if (character->name == "King")
		{
			game->set_king(client);
		}

	}
	else
	{
		game->character_deck.cards.erase(game->character_deck.cards.begin() + card);
	}
	

	switch_state = game->character_deck.cards.empty();

	if (!switch_state)
	{
		if(DiscardState)
		{
			DiscardState = false;
		}
		else
		{
			DiscardState = true;
			game->change_player();
		}
	}
}

void round_start_state::update()
{
	if (switch_state)
	{
		//TODO:
		Game::instance()->go_to_state<turn_state>(true);
	}
}
