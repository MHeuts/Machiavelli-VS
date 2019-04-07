#include "pch.h"
#include "deck.h"
#include <random>
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

player_card deck::get_character_card()
{
	auto card = player_cards_.back();
	player_cards_.pop_back();
	return card;
}

player_card deck::get_character_card(int index)
{
	auto card = player_cards_.at(index);
	player_cards_.erase(player_cards_.begin() + index);
	return card;
}

std::vector<building_card> deck::get_cards(int ammount)
{
	std::vector<building_card> cards;
	auto it = std::next(building_cards_.begin(), ammount);
	std::move(building_cards_.begin(), it, std::back_inserter(cards));
	building_cards_.erase(building_cards_.begin(), it);
	return cards;
}

void deck::BuildBuildingDeck()
{
	building_cards_.clear();

	filereader fr;
	building_cards_ = fr.read_building_cards();
	shuffle();
}

void deck::BuildCharacterDeck()
{
	player_cards_.clear();

	filereader fr;
	player_cards_ = fr.read_player_cards();
	std::shuffle(player_cards_.begin(), player_cards_.end(), std::mt19937(std::random_device()()));
}

void deck::shuffle()
{
	std::shuffle(building_cards_.begin(), building_cards_.end(), std::mt19937(std::random_device()()));
}

