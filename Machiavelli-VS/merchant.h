#pragma once

#include "player_card.h"

class mage : public player_card
{
public:
	mage(int id, std::string name) : player_card(id, name) {}
};