#include "pch.h"
#include "Assassin.h"
#include "Game.h"

assassin::assassin() : player_card("Assassin")
{
}

void assassin::ability_update() const
{
	//Game::instance()->go_to_state<MurderState>();
}
