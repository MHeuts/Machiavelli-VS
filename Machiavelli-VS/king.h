#pragma once
#include "Character.h"


class king : public character
{
public:
	king(int order ) : character(order)
	{
		color_ = YELLOW;
		name_ = "king";
		description_ = "becomes the leader for next round and gains extra income from yellow buildings";
	}
	void start_character(Game& game, Player& player) override;
};
