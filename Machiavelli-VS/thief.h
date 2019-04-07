#pragma once
#include "Character.h"


class thief : public character
{
	bool choosing_character = false;
	void print_stealing_options(Game & game, Player & player);
	void character_options(Game& game, Player& player) override;
public:
	thief(int order) : character(order) 
	{
		name_ = "robber";
		description_ = "can steal money";
	}

	void print_options(Game& game, Player& player) override;

};
