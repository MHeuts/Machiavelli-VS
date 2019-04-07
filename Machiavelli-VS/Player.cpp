//
//  Player.cpp
//  socketexample
//
//  Created by Bob Polis on 23-11-15.
//  Copyright © 2015 Avans Hogeschool, 's-Hertogenbosch. All rights reserved.
//

#include "pch.h"
#include "player.h"
using namespace std;

void Player::setup(std::vector<building_card> cards)
{
	_gold = 2;
	_city.clear();
	_buildingHand = std::move(cards);
}
