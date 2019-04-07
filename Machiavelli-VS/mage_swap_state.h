#pragma once

#include "State.h"

class mage_swap_state : public State
{
	std::shared_ptr<ClientInfo> opponent;

	bool trade_cards = false;

public:
	mage_swap_state();

	explicit mage_swap_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;
};