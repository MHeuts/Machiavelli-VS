#pragma once
#include "player_card.h"


class condotierre : public player_card
{
public:
	condotierre();

	void ability_update() const noexcept override;
};

