#pragma once

#include "State.h"

class thief_state : public State
{
	std::shared_ptr<player_card> character;
	std::shared_ptr<ClientInfo> opponent;
	bool stole_from_opponent = false;

public:
	thief_state();

	explicit thief_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void leave_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;
};
