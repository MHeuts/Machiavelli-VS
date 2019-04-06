#pragma once
#include "ClientCommand.h"
#include "ClientInfo.h"

class BaseState {
public:
	BaseState() = default;
	~BaseState() = default;

	virtual void Enter() {};
	virtual void Leave() {};
	virtual void Resume() {};
	virtual void display(std::shared_ptr<ClientInfo>& client) {};
	virtual void handle_command(const ClientCommand& command) {};
};
