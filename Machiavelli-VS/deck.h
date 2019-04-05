#pragma once
#include <vector>
#include "building_card.h"
#include "player_card.h"

class deck
{
	std::vector<building_card> building_card_;
	std::vector<player_card> player_cards_;



public:
	deck();
	deck(std::vector<building_card> building_cards, std::vector<player_card> player_cards)
		: building_card_(building_cards), player_cards_(player_cards) {};


};
