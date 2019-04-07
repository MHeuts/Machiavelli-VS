#include "pch.h"
#include "King.h"
#include "Game.h"

king::king() : player_card("King", "yellow")
{
}

void king::ability() const
{
	Game::instance()->current_client->set_message(
		"Info: The king gives you the upper hand when selecting new character cards."
	);
}
