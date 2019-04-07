#include "pch.h"
#include "Game.h"
#include "ClientInfo.h"
#include "LobbyState.h"
#include "DrawCharacterState.h"

Game::Game()
{
	stateMachine.push_state<LobbyState>();
}

void Game::HandleClientCommand(const ClientCommand& command)
{

	stateMachine.handle_command(command);
}

static std::shared_ptr<Game> instance_;

std::shared_ptr<Game> Game::instance()
{
	if (instance_ == nullptr) instance_ = std::make_shared<Game>();
	return instance_;
}

void Game::AddClient(std::weak_ptr<ClientInfo> client)
{
	clients.push_back(client);
}

void Game::setup()
{

	deck_.BuildDeck();
	clients[0].lock()->get_player().setKing(true);
	running_ = true;
	for (auto client = clients.begin(); client != clients.end(); ++client)
	{
		auto& player = client->lock()->get_player();

		player.setup(std::move(deck_.get_cards(4)));
		
	}
	stateMachine.pop_state();
	stateMachine.push_state<DrawCharacterState>();
}
