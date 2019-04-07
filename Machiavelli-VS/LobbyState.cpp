#include "pch.h"
#include "LobbyState.h"
#include "Game.h"
#include "DrawCharacterState.h"

LobbyState::LobbyState() : LobbyState(nullptr)
{
}

LobbyState::LobbyState(const std::shared_ptr<State>& old_state) : State(old_state)
{
}

void LobbyState::render(std::shared_ptr<ClientInfo>& client_info)
{
	std::stringstream message;

	message << "You are currently in the lobby." << Socket::endl;

	if (Game::instance()->number_of_clients() < 2)
	{
		message << Socket::endl << "Please wait for the other player to connect." << Socket::endl;
	}

	client_info->get_socket() << message.str();
}

void LobbyState::update()
{
	const auto game = Game::instance();

	if (game->client1 == nullptr || game->client2 == nullptr) return;

	if (game->client1->get_player().is_complete() && game->client2->get_player().is_complete())
	{
		game->go_to_state<DrawCharacterState>(true);
	}
}
