#pragma once
#include "Character.h"


class condotierre : public character
{
	bool choosing_cards = false;
	void print_choices(Game& game, Player& player);
	void character_options(Game& game, Player& player) override;
public:
	condotierre(int order) : character(order)
	{
		color_ = RED;
		name_ = "condotierre";
		description_ = "can destroy buildings of other players and gets extra income for red";
	}
	void print_options(Game& game, Player& player) override;
	
};
