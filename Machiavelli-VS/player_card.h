#pragma once
#include <string>
#include <utility>
#include "color_enum.h"
#include "Character.h"

class player_card 
{
	std::string name_;
	int number_;
	color color_;
public:
	player_card();
	player_card(int const number, std::string name)
		: name_(std::move(name)), number_(number), color_(NONE) {};

	std::string getName() { return name_; }
};
