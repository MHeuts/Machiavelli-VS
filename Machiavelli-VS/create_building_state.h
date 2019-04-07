#pragma once

#include "State.h"

class create_building_state : public State
{
public:
	create_building_state();

	explicit create_building_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;

	static std::string cards_view();
};
