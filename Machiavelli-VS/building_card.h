#pragma once

#include <string>
#include "card.h"

class BuildingCard : public Card
{
public:
	const std::string name;
	const int price;
	const std::string color;
	const std::string ability;

	// When built by preacher
	bool protected_card = false;
	bool is_built = false;

	BuildingCard(std::string name, int price, std::string color, std::string ability) :
		name(name), price(price), color(color), ability(ability) {};

	std::string to_string() const noexcept override
	{
		return name + " (" + color + ", " + std::to_string(price) + ")";
	};
};
