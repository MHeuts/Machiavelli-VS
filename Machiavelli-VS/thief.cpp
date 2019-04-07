#include "pch.h"
#include "thief.h"
Thief::Thief() : CharacterCard("Thief")
{
}

void Thief::ability_update() const noexcept
{
	//Game::instance()->go_to_state<StealState>();
}