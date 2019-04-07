#pragma once
#include "player_card.h"


class thief : public player_card
{
public:
	thief();

	void ability_update() const noexcept override;
};
