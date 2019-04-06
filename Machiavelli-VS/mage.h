#pragma once
#include "Character.h"


class mage : public character
{
	void character_options(Game& game, Player& player) override;
	bool choosing_cards = false;
	void choosing_options(Game & game, Player & player);
public:
	mage(int order) : character(order)
	{
		name_ = "mage";
		description_ = "can trade building card hand with other player";
	}
	void print_options(Game& game, Player& player) override;

};
