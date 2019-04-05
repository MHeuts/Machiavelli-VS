#pragma once
#include <string>
#include <utility>

class player_card
{
private:
	std::string name_;
	int number_;
public:
	player_card();
	player_card(int const number, std::string name )
		: name_(std::move(name)), number_(number) {};
};
