#include "pch.h"
#include "mage.h"
#include "mage_swap_state.h"
#include "Game.h"

mage::mage() : player_card("Mage")
{
}

void mage::ability_update() const
{
	Game::instance()->go_to_state<mage_swap_state>();
}
