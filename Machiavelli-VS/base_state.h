#pragma once
#include "ClientCommand.h"

class base_state {
	base_state() = default;
	virtual ~base_state() = default;

	virtual void enter() { }
	virtual void leave() { }
	virtual void resume() { }
	virtual void display(std::shared_ptr<ClientInfo>& client) { }
	virtual void handle_command(const ClientCommand& command) { }
};
