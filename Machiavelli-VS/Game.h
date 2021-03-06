#pragma once

#include "Player.h"
#include "ClientInfo.h"
#include "ClientCommand.h"
#include "player_deck.h"
#include "State.h"
#include "player_card.h"
#include "building_deck.h"

class State;

class Game
{
	std::shared_ptr<State> current_state;

	Game() noexcept;

public:
	int round = 0;

	std::shared_ptr<player_card> current_card = nullptr;

	player_deck character_deck;
	building_deck building_deck;

	std::shared_ptr<ClientInfo> client1;
	std::shared_ptr<ClientInfo> client2;

	std::shared_ptr<ClientInfo> current_client;
	std::shared_ptr<ClientInfo> winner;

	static std::shared_ptr<Game> instance() noexcept;

	bool is_running() const noexcept;

	void handle_input(std::shared_ptr<ClientCommand>& command) const noexcept;

	void render(std::shared_ptr<ClientInfo>& client_info) const noexcept;

	void update() const noexcept;

	void log(const std::shared_ptr<ClientInfo> client, const std::string message) const noexcept;

	// Clients

	int number_of_clients() const noexcept;

	void add_client(const std::shared_ptr<ClientInfo>& client) noexcept;

	void remove_client(const std::shared_ptr<ClientInfo>& shared_ptr) noexcept;

	void exit_current_state(const std::shared_ptr<State> old_state) noexcept;

	void change_player() noexcept;

	void set_player(const std::shared_ptr<ClientInfo> client) noexcept;

	void set_king(const std::shared_ptr<ClientInfo> client) const noexcept;

	template<class TState>
	void go_to_state(const bool clean = false) noexcept;
};

template<typename TState>
void Game::go_to_state(const bool clean) noexcept
{
	if (current_state != nullptr)
	{
		current_state->leave_state();
	}

	if (clean)
	{
		current_state = std::shared_ptr<State>(new TState());
	}
	else
	{
		auto new_state = std::shared_ptr<State>(new TState());
		new_state->set_old_state(current_state);
		current_state = new_state;
	}

	if (current_state != nullptr)
	{
		current_state->enter_state();
	}
}

