#include "pch.h"
#include "mage.h"

mage::mage() : player_card("Mage")
{
}

void mage::ability_update() const
{
	//Game::instance()->go_to_state<BuildingCardSwapState>();
}
