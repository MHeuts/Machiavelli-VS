#include "pch.h"
#include "condotierre.h"
Condotierre::Condotierre() : CharacterCard("Mercenary", "red")
{
	
}

void Condotierre::ability_update() const noexcept
{
	//Game::instance()->go_to_state<BuildingRemovalState>();
}
