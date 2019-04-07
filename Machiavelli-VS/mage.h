#pragma once
#include "Character.h"
#include "player_card.h"


class Mage : public CharacterCard
{
public:
	Mage();

	void ability_update() const noexcept override;
};
