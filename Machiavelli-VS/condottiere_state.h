#pragma once
#include "State.h"

class condotierre_state : public State
{
	std::shared_ptr<ClientInfo> opponent;

	std::string building_name;

public:
	condotierre_state();

	explicit condotierre_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;

	std::string build_cards_view() const;
};
