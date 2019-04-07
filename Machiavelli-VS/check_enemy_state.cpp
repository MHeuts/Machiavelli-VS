#include "pch.h"
#include "check_enemy_state.h"
#include "Game.h"

check_enemy_state::check_enemy_state() : check_enemy_state(nullptr)
{
}

check_enemy_state::check_enemy_state(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void check_enemy_state::enter_state()
{
	switch_state = false;
	Game::instance()->current_client->render_screen();
}

void check_enemy_state::render(std::shared_ptr<ClientInfo>& client)
{
	client->send_header();
	const auto game = Game::instance();

	if (client == game->current_client)
	{
		const auto opponent = client == game->client1 ? game->client2 : game->client1;

		client->get_socket() << "Your opponent has:" << Socket::endl << Socket::endl
			<< opponent->get_player().gold << " Gold." << Socket::endl
			<< opponent->get_player().building_cards.size() - opponent->get_player().number_built_buildings()
			<< " Building cards." << Socket::endl << Socket::endl
			<< opponent->get_player().building_cards_view() << Socket::endl << Socket::endl
			<< "Press any key to return" << Socket::endl;
	}
	else
	{
		client->get_socket() << "Please wait for the player to play their turn." << Socket::endl;
	}
}

void check_enemy_state::handle_input(std::shared_ptr<ClientCommand>& command)
{
	const auto client = command->get_client_info().lock();

	if (client != Game::instance()->current_client) return;

	switch_state = true;
}

void check_enemy_state::update()
{
	if (switch_state)
	{
		Game::instance()->exit_current_state(old_state);
	}
}
