#pragma once

#include "player_card.h"

class king : public player_card
{
public:
	king(int id, std::string name) : player_card(id, name) {}
};