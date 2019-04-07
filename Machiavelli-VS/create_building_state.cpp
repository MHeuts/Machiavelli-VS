#include "pch.h"
#include "create_building_state.h"
#include "Game.h"
#include "random.h"

create_building_state::create_building_state() : create_building_state(nullptr)
{
}

create_building_state::create_building_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void create_building_state::enter_state()
{
	const auto game = Game::instance();

	if (!game->current_card->can_build_buildings(game->current_client->get_player().number_built_buildings()))
	{
		game->current_client->set_message("You have reached the maximum of 8 buildings.");
		switch_state = true;
		return;
	}

	if (game->current_client->get_player().get_turn().built_buildings() >= game->current_card->number_buildable_buildings)
	{
		game->current_client->set_message("You already build the maximum number of buildings for this turn.");
		switch_state = true;
		return;
	}

	game->current_client->render_screen();
}

void create_building_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();

	const auto game = Game::instance();
	if (client == game->current_client)
	{
		const auto cards = client->get_player().building_cards.size() - client->get_player().number_built_buildings();
		const auto opponent = client == game->client1 ? game->client2 : game->client1;

		client->get_socket() << cards_view() << "(" << cards + 1 << ") Go back."
			<< Socket::endl << Socket::endl
			<< "Pick one building." << Socket::endl << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to play their turn." << Socket::endl;
	}
}

void create_building_state::handle_input(std::shared_ptr<ClientCommand>& command)
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

	std::shared_ptr<building_card> found_card = nullptr;
	const auto cards = client->get_player().building_cards;

	if (action == client->get_player().building_cards.size() - client->get_player().number_built_buildings())
	{
		switch_state = true;
		return;
	}

	// If the user already built their allowed number of buildings
	if (client->get_player().get_turn().built_buildings() >= game->current_card->number_buildable_buildings)
	{
		client->set_message("You already build the maximum number of buildings for this turn.");
		return;
	}

	int index = 0;
	for (const auto& card : cards)
	{
		if (card->is_built) continue;

		if (index == action)
		{
			found_card = card;
			break;
		}

		index++;
	}

	if (found_card == nullptr)
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	if (client->get_player().gold < found_card->price)
	{
		client->set_message("You don't have enough gold to build this building.");
		return;
	}

	game->current_card->build_building(found_card);
	client->get_player().gold -= found_card->price;
	client->get_player().get_turn().build_building();
	client->set_message("You built a " + found_card->name + ".");

	if (client->get_player().number_built_buildings() == 8 && game->winner == nullptr)
	{
		game->winner = client;
	}
}

void create_building_state::update()
{
	if (switch_state)
	{
		Game::instance()->exit_current_state(old_state);
	}
}

std::string create_building_state::cards_view()
{
	std::stringstream string;

	string << "Select a building you want to build:" << Socket::endl;

	int index = 1;
	for (const auto& card : Game::instance()->current_client->get_player().building_cards)
	{
		if (card->is_built) continue;

		string << "(" << index++ << ") " << card->to_string() << Socket::endl;
	}

	return string.str();
}
