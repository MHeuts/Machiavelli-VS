#pragma once

#include "player_card.h"

class assassin : public player_card
{
public:
	assassin(int id, std::string name) : player_card(id, name) {}
};