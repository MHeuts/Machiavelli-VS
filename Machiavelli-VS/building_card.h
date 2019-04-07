#pragma once
#include <string>
#include <utility>

class building_card 
{
	std::string name_;
	int cost_;
	int color_;

public:
	building_card(); 
	explicit building_card(std::string const name, int const number, int const color)
		: name_(std::move(name)), cost_(number), color_(color) {}

	void name(std::string name);
	std::string name() const;
	void color(int color);
	int color() const;
	void cost(int cost);
	int cost() const;

	std::string to_string() const { return "name: "+ name_ + "color: " + std::to_string(color_) + "cost: " + std::to_string(cost_); }
}; 
