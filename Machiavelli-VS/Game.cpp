#include "pch.h"
#include "Game.h"
#include "ClientInfo.h"

void Game::HandleClientCommand(const ClientCommand& command) {

	stateMachine.handle_command(command);

	if (auto clientInfo = command.get_client_info().lock()) {

		auto &client = clientInfo->get_socket();
		client << "test\n";
	}
}


static std::shared_ptr<Game> instance_;

std::shared_ptr<Game> Game::instance() {
	if (instance_ == nullptr) instance_ = std::make_shared<Game>();
	return instance_;
}

void Game::AddClient(std::weak_ptr<ClientInfo> client)
{
	clients.push_back(client);
}

void Game::setup()
{
}
