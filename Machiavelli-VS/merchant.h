#pragma once
#include "Character.h"


class mage : public character
{
public:
	mage(int order) : character(order)
	{
		color_ = GREEN;
		name_ = "merchant";
		description_ = "gets 1 extra income and extra from green buildings";
	}
	void start_character(Game& game, Player& player) override;
};
