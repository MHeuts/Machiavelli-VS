#pragma once
#include "player_card.h"


class Condotierre : public CharacterCard
{
public:
	Condotierre();

	void ability_update() const noexcept override;
};

