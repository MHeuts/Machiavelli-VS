#pragma once
#include "Character.h"


class preacher : public character
{
public:
	preacher(int order) : character(order)
	{
		color_ = BLUE;
		name_ = "preacher";
		description_ = "stops condotierre from destroying buildings and gets income from blue buildings";
	}
	void start_character(Game& game, Player& player) override;
};
