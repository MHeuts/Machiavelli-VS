#include "pch.h"
#include "deck.h"
#include "random.h"
#include "file_reader.h"

deck::deck()
{
	filereader fr;
	building_cards_ = fr.read_building_cards();
	player_cards_ = fr.read_player_cards();
	shuffle();
}

building_card deck::get_card()
{
	auto card = building_cards_.back();
	building_cards_.pop_back();
	return card;
}

void deck::BuildDeck()
{
	building_cards_.clear();

	filereader fr;
	building_cards_ = fr.read_building_cards();
	shuffle();
}

void deck::shuffle()
{
	std::random_shuffle(building_cards_.begin(), building_cards_.end());
}

