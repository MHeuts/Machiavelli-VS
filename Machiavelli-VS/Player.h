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

#include <string>
#include <vector>
#include "Character.h"
#include "Building.h"

class Player {
public:
	Player() {}
	Player(const std::string& name) : name{ name } {}

	std::string get_name() const { return name; }
	void set_name(const std::string& new_name) { name = new_name; }

private:
	std::string name;
	int _gold;
	std::vector<Character> _characterHand;
	std::vector<Building> _buildingHand;
	std::vector<Building> _city;
};

#endif /* Player_hpp */
