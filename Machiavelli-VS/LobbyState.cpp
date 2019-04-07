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
	command.get_client_info().lock()->get_socket() << "waiting For players";
}
