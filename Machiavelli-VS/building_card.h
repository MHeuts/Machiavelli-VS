#pragma once

#include <string>
#include "card.h"

class building_card : public card
{
public:
	const std::string name;
	const int price;
	const std::string color;
	const std::string ability;

	// When built by preacher
	bool protected_card = false;
	bool is_built = false;

	building_card(std::string name, int price, std::string color, std::string ability) :
		name(name), price(price), color(color), ability(ability) {};

	std::string to_string() const noexcept override
	{
		return name + " (" + color + ", " + std::to_string(price) + ")";
	};
};
