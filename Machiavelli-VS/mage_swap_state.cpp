#include "pch.h"
#include "mage_swap_state.h"
#include "Game.h"
#include "mage_trade_state.h"

mage_swap_state::mage_swap_state() : mage_swap_state(nullptr)
{
}

mage_swap_state::mage_swap_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void mage_swap_state::enter_state()
{
	if (switch_state) return;

	const auto game = Game::instance();
	opponent = game->current_client == game->client1 ? game->client2 : game->client1;

	game->current_client->render_screen();
}

void mage_swap_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();

	if (client == Game::instance()->current_client)
	{
		client->get_socket() << "You can either:" << Socket::endl << Socket::endl
			<< "(1) Swap your cards with your opponent's, or..." << Socket::endl
			<< "(2) Trade some of your cards for new ones." << Socket::endl
			<< "(3) Go Back." << Socket::endl << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to play their turn." << Socket::endl;
	}
}

void mage_swap_state::handle_input(std::shared_ptr<ClientCommand>& command)
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

	if (action == 1)
	{
		std::vector<std::shared_ptr<building_card>> player1_cards;
		std::vector<std::shared_ptr<building_card>> player2_cards;

		for (const auto card : game->client1->get_player().building_cards)
		{
			if (card->is_built) continue;

			player2_cards.push_back(card);
		}

		for (const auto card : game->client2->get_player().building_cards)
		{
			if (card->is_built) continue;

			player1_cards.push_back(card);
		}

		for (const auto card : player2_cards)
		{
			game->client2->get_player().building_cards.push_back(card);

			game->client1->get_player().building_cards.erase(std::find(
				game->client1->get_player().building_cards.begin(),
				game->client1->get_player().building_cards.end(),
				card
			));
		}

		for (const auto card : player1_cards)
		{
			game->client1->get_player().building_cards.push_back(card);

			game->client2->get_player().building_cards.erase(std::find(
				game->client2->get_player().building_cards.begin(),
				game->client2->get_player().building_cards.end(),
				card
			));
		}

		client->set_message("You swapped your cards with your opponent's.");
		opponent->set_message("The mage swapped your cards with your opponent's.");

		client->get_player().get_turn().use_ability();

		switch_state = true;
		return;
	}

	if (action == 2)
	{
		trade_cards = true;
		return;
	}

	if (action == 3)
	{
		switch_state = true;
		return;
	}

	client->set_message("Invalid input, please try again.");
}

void mage_swap_state::update()
{
	auto game = Game::instance();

	if (trade_cards)
	{
		game->go_to_state<mage_trade_state>();
		trade_cards = false;
		switch_state = true;
		return;
	}

	if (switch_state)
	{
		game->exit_current_state(old_state);
	}
}
