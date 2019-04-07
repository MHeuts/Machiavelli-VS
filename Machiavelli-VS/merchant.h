#pragma once
#include "player_card.h"

class merchant : public player_card
{
public:
	merchant();

	void ability() const override;

	int bonus() const override;
};
