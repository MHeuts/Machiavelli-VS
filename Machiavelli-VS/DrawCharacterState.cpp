#include "pch.h"
#include "DrawCharacterState.h"
#include "Game.h"

void DrawCharacterState::Enter()
{
	auto game = Game::instance();
	game->setCurrentPlayer(game->getKing());
}

void DrawCharacterState::handle_command(const ClientCommand& command)
{
	auto selected_card = std::stoi(command.get_cmd());
}
