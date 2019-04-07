#include "pch.h"
#include "architect.h"
#include "Game.h"

architect::architect() : player_card("Architect")
{
	number_buildable_buildings = 3;
	pickable_buildings = 2;
}

void architect::ability() const noexcept
{
	Game::instance()->current_client->set_message(
		"Info: The Architect will allow you to pick and build multiple buildings."
	);
}

bool architect::can_build_buildings(const int number_built) const noexcept
{
	return true;
}

