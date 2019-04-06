#pragma once
#include "StateMachine.h"
#include "player.h"

class Player;

class Game {


	StateMachine stateMachine;

	bool finished_ = false;


	std::vector<std::shared_ptr<ClientInfo>> clients_;

public:
	Player & other_player(Player& player);

};
