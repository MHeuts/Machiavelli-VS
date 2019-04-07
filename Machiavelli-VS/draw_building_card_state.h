#pragma once
#include "building_card.h"
#include "State.h"

class draw_building_card_state : public State
{
	std::vector<std::shared_ptr<building_card>> cards;
	std::shared_ptr<building_card> selected_card;

public:
	draw_building_card_state();

	explicit draw_building_card_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void leave_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;

	std::string cards_view() const;

	void select_random_cards();
};
