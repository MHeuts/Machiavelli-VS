#pragma once

#include "player_card.h"

class builder : public CharacterCard
{
public:
	builder();

	void ability() const noexcept override;

	bool can_build_buildings(int number_built) const noexcept override;
};