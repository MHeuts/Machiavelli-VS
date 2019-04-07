#include "pch.h"
#include "mage.h"

Mage::Mage() : CharacterCard("Mage")
{
}

void Mage::ability_update() const noexcept
{
	//Game::instance()->go_to_state<BuildingCardSwapState>();
}
