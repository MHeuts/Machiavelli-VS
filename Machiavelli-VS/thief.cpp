#include "pch.h"
#include "thief.h"
#include "thief_state.h"
#include "Game.h"

thief::thief() : player_card("Thief")
{
}

void thief::ability_update() const
{
	Game::instance()->go_to_state<thief_state>();
}