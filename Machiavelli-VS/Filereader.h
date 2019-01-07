#pragma once
#include <vector>
#include "Card.h"
#include "playerCard.h"

class filereader
{
public:
	building_card create_building_card(std::vector<std::string> attributes) const; 
	player_card create_player_card(const std::string& attributes) const;
	std::vector<player_card> read_player_cards() const;
	std::vector<building_card> read_building_cards() const;
};
