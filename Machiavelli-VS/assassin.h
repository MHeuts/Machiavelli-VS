#pragma once
#include "player_card.h"

class assassin : public player_card
{
public:
	assassin();

	void ability_update() const noexcept override;
};
