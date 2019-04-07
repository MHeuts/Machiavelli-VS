#pragma once
#include "player_card.h"


class Thief : public CharacterCard
{
public:
	Thief();

	void ability_update() const noexcept override;
};
