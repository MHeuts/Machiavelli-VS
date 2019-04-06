#include "pch.h"
#include "LobbyState.h"
#include "Game.h"

void LobbyState::handle_command(const ClientCommand& command)
{
	auto game = Game::instance();

    if (game->PlayersReady()) {
        game->setup();
        return;
    }

	

	const auto client = command.get_client_info().lock();

	if (auto clientInfo = command.get_client_info().lock()) {

		auto &client = clientInfo->get_socket();
		client << "test\n";
	}
}

