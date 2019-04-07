#include "pch.h"
#include "assassin.h"
#include "Game.h"
#include "assassin_state.h"

assassin::assassin() : player_card("Assassin")
{
}

void assassin::ability_update() const
{
	Game::instance()->go_to_state<assassin_state>();
}
