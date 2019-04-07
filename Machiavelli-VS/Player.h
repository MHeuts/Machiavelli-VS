#pragma once
//
//  Player.hpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#ifndef Player_h
#define Player_h

class player_card;
class building_card;

#include <string>
#include "Socket.h"
#include "building_card.h"
#include "player_card.h"
#include "Turn.h"
class Player
{
	Turn current_turn;

public:
	const std::string name;
	const int age = -1;

	int gold = 0;
	bool is_king = false;

	std::vector<std::shared_ptr<player_card>> character_cards;
	std::vector<std::shared_ptr<building_card>> building_cards;

	Player() = default;

	explicit Player(const std::string& name) noexcept;

	explicit Player(const std::string& name, const int age) noexcept;

	bool is_complete() const noexcept;

	Turn& get_turn() noexcept;

	void start_turn() noexcept;

	std::shared_ptr<player_card> has_card(const std::shared_ptr<player_card>& card) const noexcept;

	std::string building_cards_view() const noexcept;

	std::string cards_view() const noexcept;

	int number_built_buildings() const noexcept;
};
#endif /* Player_hpp */
