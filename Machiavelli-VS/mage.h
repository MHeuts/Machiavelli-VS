#pragma once
#include "Character.h"
#include "player_card.h"


class mage : public player_card
{
public:
	mage();

	void ability_update() const override;
};
