#pragma once
#include <vector>
#include "filereader.h"
#include "player_card.h"

class player_deck : public file_reader
{
	void make_card(const std::string& name, int order) noexcept;

	std::vector<std::shared_ptr<player_card>> original_cards;

public:
	std::vector<std::shared_ptr<player_card>> cards;

	void reset() noexcept;

	friend std::ifstream& operator>>(std::ifstream& ifstream, player_deck& deck) noexcept;

	friend std::ostream& operator<<(std::ostream& ostream, player_deck& deck) noexcept;

	std::string to_string() const noexcept;

	std::vector<std::shared_ptr<player_card>> get_original_cards() const noexcept;

	std::string print_original_cards() const noexcept;
};
