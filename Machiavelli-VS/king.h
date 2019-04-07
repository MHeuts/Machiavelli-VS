#pragma once
#include "player_card.h"


class king : public player_card
{
public:
	king();

	void ability() const noexcept override;
};
