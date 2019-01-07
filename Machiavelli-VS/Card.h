#pragma once
#include <string>
#include <utility>

class building_card
{
private:
	std::string name_;
	int cost_;
	int color_;

public:
	building_card(); 
	explicit building_card(std::string const name, int const number, int const color)
		: name_(std::move(name)), cost_(number), color_(color) {}

	void name(std::string const name);
	std::string const name() const;
	void color(int const color);
	int const color() const;
	void cost(int const cost);
	int const cost() const;

	
}; 
enum color
{
	RED,
	GREEN,
	BLUE,
	YELLOW
};
