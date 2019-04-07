#pragma once

#include "State.h"
#include "Game.h"

class round_start_state : public State
{
private:
	bool DiscardState{ false };
public:
	round_start_state();

	explicit round_start_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void leave_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;
};
