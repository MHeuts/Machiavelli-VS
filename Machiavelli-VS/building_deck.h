#pragma once

#include <vector>
#include "filereader.h"
#include "building_card.h"
#include <memory>

class building_deck : public file_reader
{
	std::vector<std::shared_ptr<building_card>> original_cards;

public:
	std::vector<std::shared_ptr<building_card>> cards;

	void reset();

	friend std::ifstream& operator>>(std::ifstream& ifstream, building_deck& deck);

	friend std::ostream& operator<<(std::ostream& ostream, const building_deck& deck);
};
