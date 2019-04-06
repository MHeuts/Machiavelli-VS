#pragma once
#include "StateMachine.h"

class Game {
private:
	StateMachine stateMachine;
public:
	Game() = default;;
	~Game() = default;
	void HandleClientCommand(std::shared_ptr<ClientCommand>& command);

	static std::shared_ptr<Game> instance();

};
