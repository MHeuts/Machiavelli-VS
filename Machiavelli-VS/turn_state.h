#pragma once

#include "State.h"
#include "Game.h"

class turn_state : public State
{
	int current_order = 0;
	bool use_ability = false;

	// State switching booleans
	bool building_building = false;
	bool pick_building_card = false;

public:
	turn_state();

	explicit turn_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;

	void determine_next_player();

	bool check_player_card(const std::shared_ptr<ClientInfo> client, const std::shared_ptr<player_card> card) const;

	static std::string round_header(const std::shared_ptr<ClientInfo> client);

	void switch_card(const std::shared_ptr<ClientInfo>& client, const std::shared_ptr<player_card>& card) const;
};
