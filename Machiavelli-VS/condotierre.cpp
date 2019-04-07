#include "pch.h"
#include "condotierre.h"
#include "condottiere_state.h"
#include "Game.h"

condotierre::condotierre() : player_card("Condotierre", "red"){}

void condotierre::ability_update() const 
{
	Game::instance()->go_to_state<condotierre_state>();
}
