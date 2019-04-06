#pragma once
#include "ClientCommand.h"

class BaseState {
	BaseState() = default;
	~BaseState() = default;

	virtual void Enter() {};
	virtual void Leave() {};
	virtual void display(std::shared_ptr<ClientInfo>& client) {};
	virtual void handle_command(std::shared_ptr<ClientCommand>& command) {};
};
