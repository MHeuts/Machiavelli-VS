#pragma once

#include "player_card.h"

class preacher : public player_card
{
public:
	preacher(int id, std::string name) : player_card(id, name) {}
};