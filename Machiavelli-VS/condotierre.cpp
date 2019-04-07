#include "pch.h"
#include "condotierre.h"
condotierre::condotierre() : player_card("Mercenary", "red")
{
	
}

void condotierre::ability_update() const noexcept
{
	//Game::instance()->go_to_state<BuildingRemovalState>();
}
