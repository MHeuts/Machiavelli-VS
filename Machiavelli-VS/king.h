#pragma once
#include "player_card.h"


class King : public CharacterCard
{
public:
	King();

	void ability() const noexcept override;
};
