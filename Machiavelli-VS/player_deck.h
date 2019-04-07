#pragma once
#include <vector>
#include "filereader.h"
#include "player_card.h"

class player_deck : public file_reader
{
	void make_card(const std::string& name, int order);

	std::vector<std::shared_ptr<player_card>> original_cards;

public:
	std::vector<std::shared_ptr<player_card>> cards;

	void reset();

	friend std::ifstream& operator>>(std::ifstream& ifstream, player_deck& deck);

	friend std::ostream& operator<<(std::ostream& ostream, player_deck& deck);

	std::string to_string() const;

	std::vector<std::shared_ptr<player_card>> get_original_cards() const;

	std::string print_original_cards() const;
};
