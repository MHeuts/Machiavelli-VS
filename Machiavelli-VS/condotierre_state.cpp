#include "pch.h"
#include "condottiere_state.h"
#include "Game.h"
#include <algorithm>

condotierre_state::condotierre_state() : condotierre_state(nullptr)
{
}

condotierre_state::condotierre_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void condotierre_state::enter_state()
{
	const auto game = Game::instance();
	opponent = game->current_client == game->client1 ? game->client2 : game->client1;

	game->current_client->render_screen();
}

void condotierre_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();

	const auto game = Game::instance();
	if (client == game->current_client)
	{
		if (opponent->get_player().number_built_buildings() >= 8)
		{
			client->get_socket() << "Your opponent has capped his city, you can't destroy anything anymore"
				<< Socket::endl << Socket::endl
				<< "Press any key to return" << Socket::endl;
			return;
		}

		client->get_socket() << "Your opponent has the following buildings:" << Socket::endl << Socket::endl
			<< build_cards_view()
			<< "(" << opponent->get_player().number_built_buildings() + 1
			<< ") Go back." << Socket::endl << Socket::endl
			<< "Pick a building to destroy."
			<< Socket::endl << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to play their turn." << Socket::endl;
	}
}

void condotierre_state::handle_input(std::shared_ptr<ClientCommand>& command)
{
	const auto game = Game::instance();
	const auto client = command->get_client_info().lock();

	if (client != game->current_client) return;

	if (opponent->get_player().number_built_buildings() >= 8)
	{
		switch_state = true;
		return;
	}

	int action = -1;
	try
	{
		action = atoi(command->get_cmd().c_str());
	}
	catch (...) {}
	action--;

	if (action == opponent->get_player().number_built_buildings())
	{
		switch_state = true;
		return;
	}

	if (action < 0 || action >= opponent->get_player().number_built_buildings())
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	std::shared_ptr<building_card> found_card = nullptr;

	auto opp = opponent->get_player().building_cards;

	std::vector<std::shared_ptr<building_card>> buildings;
	std::copy_if(opp.begin(), opp.end(), std::back_inserter(buildings), [](std::shared_ptr<building_card> item) {
		return item->is_built;
	});

	int index = 0;
	for (auto& item : buildings)
	{
		if (index == action)
		{
			found_card = item;
			break;
		}

		index++;
	}

	if (found_card == nullptr)
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	if (found_card->protected_card)
	{
		client->set_message("This card is protected by the preacher!, please pick another one.");
		return;
	}

	if (client->get_player().gold < found_card->price - 1)
	{
		client->set_message("You do not have enough gold to destroy this building");
		return;
	}

	client->get_player().gold -= (found_card->price - 1);
	building_name = found_card->name;

	found_card->is_built = false;
	found_card->protected_card = false;

	opponent->get_player().building_cards.erase(std::find(
		opponent->get_player().building_cards.begin(), opponent->get_player().building_cards.end(), found_card)
	);

	opponent->set_message("Your opponent destroyed your " + building_name + ".");
	client->set_message("You destroyed your opponent's " + building_name + ".");

	client->get_player().get_turn().use_ability();

	switch_state = true;
}

void condotierre_state::update()
{
	if (switch_state)
	{
		Game::instance()->exit_current_state(old_state);
	}
}

std::string condotierre_state::build_cards_view() const
{
	std::stringstream view;

	auto index = 1;
	for (const auto& card : opponent->get_player().building_cards)
	{
		if (!card->is_built) continue;

		view << "(" << index++ << ") " << card->to_string() << Socket::endl;
	}

	return view.str();
}
