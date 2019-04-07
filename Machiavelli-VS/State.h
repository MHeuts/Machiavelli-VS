#pragma once

#include <memory>
#include "ClientInfo.h"
#include "ClientCommand.h"

class State
{
protected:
	std::shared_ptr<State> old_state;

	bool switch_state = false;

public:
	State();

	explicit State(const std::shared_ptr<State> old_state);

	virtual ~State() = default;

	virtual void enter_state() {}

	virtual void leave_state() {}

	virtual void render(std::shared_ptr<ClientInfo>& client) {}

	virtual void handle_input(std::shared_ptr<ClientCommand>& command) {}

	virtual void update() {}

	std::shared_ptr<State> get_old_state() const;

	void set_old_state(const std::shared_ptr<State> state);
};

