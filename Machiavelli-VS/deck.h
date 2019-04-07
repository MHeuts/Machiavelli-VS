#pragma once
#include <utility>
#include <vector>
#include "building_card.h"
#include "player_card.h"

class deck
{
	std::vector<building_card> building_cards_;
	std::vector<player_card> player_cards_;
	void shuffle();

public:
	deck();

	deck(std::vector<building_card> building_cards, std::vector<player_card> player_cards)
		: building_cards_(std::move(building_cards)), player_cards_(std::move(player_cards)) 
	{
		shuffle();
	}

	void BuildDeck();

	building_card get_card();

	std::vector<building_card> get_cards(int ammount);

	std::vector<building_card>& get_building_cards() { return building_cards_; };

	std::vector<player_card>& get_player_cards() { return player_cards_; };
	void remove_card(int card) { player_cards_.erase(player_cards_.begin() + card); }
	
};
