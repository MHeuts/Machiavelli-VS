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
	if (&command.get_client_info().lock()->get_player() != &getCurrentClient()->get_player()) {
		command.get_client_info().lock()->get_socket() << "Not your turn\r\n";
	}
	else {
		stateMachine.update();
		stateMachine.handle_command(command);
	}
}

static std::shared_ptr<Game> instance_;

std::shared_ptr<Game> Game::instance()
{
	if (instance_ == nullptr) instance_ = std::make_shared<Game>();
	return instance_;
}

void Game::AddClient(std::shared_ptr<ClientInfo> client)
{
	clients_.push_back(client);
	if (PlayersReady())
		setup();
}

void Game::setup()
{
	deck_.BuildBuildingDeck();
	clients_[0]->get_player().setKing(true);
	running_ = true;
	for (auto client = clients_.begin(); client != clients_.end(); ++client)
	{
		auto& player = client->get()->get_player();
		player.setup(std::move(deck_.get_cards(4)));
	}

	currentKing_ = 0;
	stateMachine.pop_state();
	stateMachine.push_state<DrawCharacterState>();
}
