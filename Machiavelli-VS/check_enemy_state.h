#pragma once

#include "State.h"

class check_enemy_state : public State
{
public:
	check_enemy_state();

	explicit check_enemy_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;
};