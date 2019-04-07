#include "pch.h"
#include "King.h"
#include "Game.h"

King::King() : CharacterCard("King", "yellow")
{
}

void King::ability() const noexcept
{
	Game::instance()->current_client->set_message(
		"Info: The king gives you the upper hand when selecting new character cards."
	);
}
