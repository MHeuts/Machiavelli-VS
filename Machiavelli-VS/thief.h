#pragma once

#include "player_card.h"

class thief : public player_card
{
public:
	thief(int id, std::string name) : player_card(id, name) {}
};