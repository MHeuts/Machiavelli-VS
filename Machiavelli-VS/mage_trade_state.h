#pragma once
#include "State.h"

class mage_trade_state : public State
{
	int cards_traded = 0;

	std::vector<std::shared_ptr<building_card>> trade_cards;

public:
	mage_trade_state();

	explicit mage_trade_state(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void render(std::shared_ptr<ClientInfo>& client) override;

	void handle_input(std::shared_ptr<ClientCommand>& command) override;

	void update() override;

	std::string cards_view() const;

	int number_cards() const;
};