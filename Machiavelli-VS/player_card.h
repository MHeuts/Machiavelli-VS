#pragma once
#include <string>
#include <memory>
#include "card.h"
#include "building_card.h"

class Player;

class player_card : public card
{
protected:
	explicit player_card(std::string name);
	explicit player_card(std::string name, std::string color);

public:
	bool robbed = false;
	bool killed = false;

	int number_buildable_buildings = 1;
	int pickable_buildings = 1;

	const std::string name;
	const std::string color;
	int order;

	virtual void ability() const {}

	virtual void ability_update() const {}

	bool operator==(player_card right) const;

	virtual int bonus() const;

	virtual void build_building(const std::shared_ptr<building_card>& card) const;

	virtual bool can_build_buildings(int number_built) const;
};
