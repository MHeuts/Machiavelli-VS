#include "pch.h"
#include "Game.h"
#include "ClientInfo.h"

void Game::HandleClientCommand(ClientCommand& command) {

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