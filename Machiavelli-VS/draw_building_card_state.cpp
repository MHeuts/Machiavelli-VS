#include "pch.h"
#include "draw_building_card_state.h"
#include "Game.h"
#include "random.h"

draw_building_card_state::draw_building_card_state() : draw_building_card_state(nullptr)
{
}

draw_building_card_state::draw_building_card_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void draw_building_card_state::enter_state()
{
	select_random_cards();

	switch_state = false;
	Game::instance()->current_client->render_screen();
}

void draw_building_card_state::leave_state()
{
	Game::instance()->current_client->set_message("You got a " + selected_card->name + " building card.");
}

void draw_building_card_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();

	const auto game = Game::instance();
	if (client == game->current_client)
	{
		const auto opponent = client == game->client1 ? game->client2 : game->client1;

		client->get_socket() << cards_view() << Socket::endl
			<< "Pick one card." << Socket::endl << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to play their turn." << Socket::endl;
	}
}

void draw_building_card_state::handle_input(std::shared_ptr<ClientCommand>& command)
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

	if (action < 0 || action >= cards.size())
	{
		client->set_message("Invalid input, please try again.");
		return;
	}

	selected_card = cards.at(action);

	client->get_player().building_cards.push_back(selected_card);
	client->get_player().get_turn().picked_building();
	client->set_message("You got a " + selected_card->name + " card.");

	if (client->get_player().get_turn().amount_picked() >= game->current_card->pickable_buildings)
	{
		switch_state = true;
		return;
	}

	select_random_cards();
}

void draw_building_card_state::update()
{
	if (switch_state)
	{
		Game::instance()->exit_current_state(old_state);
	}
}

std::string draw_building_card_state::cards_view() const
{
	std::stringstream string;

	string << "These 2 random cards are available for you:" << Socket::endl;

	int index = 1;
	for (const auto& card : cards)
	{
		string << "(" << index++ << ") " << card->to_string() << Socket::endl;
	}

	return string.str();
}

void draw_building_card_state::select_random_cards()
{
	cards.clear();

	auto building_cards = Game::instance()->building_deck.cards;
	for (int i = 0; i < 2; ++i)
	{
		const auto index = Random::instance().get(building_cards.size() - 1);

		cards.push_back(building_cards.at(index));
		building_cards.erase(building_cards.begin() + index);
	}
}
