#include "pch.h"
#include "merchant.h"
#include "Game.h"

merchant::merchant() : player_card("Merchant", "green")
{
}

void merchant::ability() const noexcept
{
	Game::instance()->current_client->set_message(
		"Info: The merchant will receive a piece of gold when it's his turn."
	);
}

int merchant::bonus() const noexcept
{
	return player_card::bonus() + 1;
}
