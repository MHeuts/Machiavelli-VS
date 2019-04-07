#pragma once

#include "player_card.h"

class builder : public character
{
public:
	builder(int order) : character(order)
	{
		name_ = "builder";
		description_ = "can draw 2 more cards and can build 3 buildings";
	}

	void start_character(Game& game, Player& player) override;
};