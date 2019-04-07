#pragma once
#include "player_card.h"

class Assassin : public CharacterCard
{
public:
	Assassin();

	void ability_update() const noexcept override;
};
