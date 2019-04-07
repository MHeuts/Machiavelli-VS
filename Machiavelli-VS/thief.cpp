#include "pch.h"
#include "thief.h"
thief::thief() : player_card("Thief")
{
}

void thief::ability_update() const
{
	//Game::instance()->go_to_state<StealState>();
}