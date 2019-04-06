#pragma once
#include "color_enum.h"
#include "Building.h"
#include <vector>

class Game;
class Player;

class character {
protected:
	int order_ = 0;
	color color_ = NONE;
	std::string name_ = "";
	std::string description_ = "";

	bool chosen_;

	bool dead_;
	bool gold_stolen_;

	bool performed_normal_choice_ = false;
	virtual void default_options(Game& game, Player& player);

	bool choosing_building_card_ = false;
	std::vector<Building> building_cards_{};
	virtual void choose_building_options(Game& game, Player& player);

	int amount_of_buildings_ = 0;
	int max_buildings_to_build_ = 1;
	bool choosing_building_to_build(Game& game, Player& player);

	bool character_power_ = false;
	virtual void character_options(Game& game, Player& player) {};

public:
	character();
	character(int player_order) : order_(player_order) {};

	virtual ~character() = default;

	virtual void kill() { dead_ = true; };
	bool is_killed() const { return dead_; };

	std::string get_name() const { return name_; };
	std::string get_description() const { return description_; };

	virtual void start_character(Game& game, Player& player);
	virtual void print_options(Game& game, Player& player);

	int get_order() const { return order_; };

	void choose() { chosen_ = true; }
	bool is_chosen() const { return chosen_; };


};
