#pragma once

#include "player_card.h"

class condotierre : public player_card
{
public:
	condotierre(int id, std::string name) : player_card(id, name) {}
};