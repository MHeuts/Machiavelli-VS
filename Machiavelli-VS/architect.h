#pragma once

#include "player_card.h"

class architect : public player_card
{
public:
	architect();

	void ability() const override;

	bool can_build_buildings(int number_built) const override;
};