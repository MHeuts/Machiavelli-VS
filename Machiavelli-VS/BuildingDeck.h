#pragma once

#include <vector>
#include "CsvReader.h"
#include "building_card.h"
#include <memory>

class BuildingDeck : public CsvReader
{
	std::vector<std::shared_ptr<BuildingCard>> original_cards;

public:
	std::vector<std::shared_ptr<BuildingCard>> cards;

	void reset() noexcept;

	friend std::ifstream& operator>>(std::ifstream& ifstream, BuildingDeck& deck) noexcept;

	friend std::ostream& operator<<(std::ostream& ostream, const BuildingDeck& deck) noexcept;
};
