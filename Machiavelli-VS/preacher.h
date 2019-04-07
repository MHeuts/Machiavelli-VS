#pragma once
#include "building_deck.h"
#include "player_card.h"


class preacher : public player_card
{
public:
	preacher();

	void ability() const override;

	void build_building(const std::shared_ptr<building_card>& card) const override;
};
