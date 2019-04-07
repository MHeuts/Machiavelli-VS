#include "pch.h"
#include "builder.h"
#include "Game.h"

builder::builder() : CharacterCard("Architect")
{
	number_buildable_buildings = 3;
	pickable_buildings = 2;
}

void builder::ability() const noexcept
{
	Game::instance()->current_client->set_message(
		"Info: The Architect will allow you to pick and build multiple buildings."
	);
}

bool builder::can_build_buildings(const int number_built) const noexcept
{
	return true;
}

