#pragma once

#include "player_card.h"

class builder : public player_card
{
public:
	builder(int id, std::string name) : player_card(id, name) {}
};