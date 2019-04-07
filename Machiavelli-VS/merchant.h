#pragma once
#include "player_card.h"

class merchant : public player_card
{
public:
	merchant();

	void ability() const noexcept override;

	int bonus() const noexcept override;
};
