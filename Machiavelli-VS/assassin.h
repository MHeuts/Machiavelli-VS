#pragma once
#include "Character.h"

class assassin : public character
{
	void character_options(Game& game, Player& player) override;
	void show_killable_targets(Game& game, Player& player);

public:
	assassin(int order) : character(order)
	{
		name_ = "assassin";
		description_ = "has the ability to kill other characters";
	}

	void print_options(Game& game, Player& player) override;
};
