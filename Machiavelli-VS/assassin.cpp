#include "pch.h"
#include "Assassin.h"
#include "Game.h"

Assassin::Assassin() : CharacterCard("Assassin")
{
}

void Assassin::ability_update() const noexcept
{
	//Game::instance()->go_to_state<MurderState>();
}
