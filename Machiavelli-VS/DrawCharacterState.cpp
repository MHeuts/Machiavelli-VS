#include "pch.h"
#include "DrawCharacterState.h"
#include "Game.h"

void DrawCharacterState::Enter()
{
	auto game = Game::instance();
	game->setCurrentPlayer(game->getKing());
	game->getDeck().BuildCharacterDeck();
	game->getCurrentClient()->get_socket() << "You are the first player\r\n";
	auto card = game->getDeck().get_character_card();

	game->getCurrentClient()->get_socket() << card.getName() << " was the top card and has been removed!\r\n";

	showAvailibleCards();
	
}

void DrawCharacterState::handle_command(const ClientCommand& command)
{
	auto selected_card = std::stoi(command.get_cmd());
}

void DrawCharacterState::showAvailibleCards()
{
	auto &client = Game::instance()->getCurrentClient()->get_socket();
	auto characters = Game::instance()->getDeck().get_player_cards();
	client << " Available cards to pick from \r\n";

	for (int i = 0; i < characters.size(); ++i)
	{
		client << i << ": " << characters[i].getName() << "\r\n";
	}
}