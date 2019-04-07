#pragma once

#include "State.h"
#include "player_card.h"

class assassin_state : public State
{
	std::shared_ptr<player_card> character;
	std::shared_ptr<ClientInfo> opponent;
	bool killed_opponent_card = false;

public:
	assassin_state();

	explicit assassin_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void leave_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;
};
