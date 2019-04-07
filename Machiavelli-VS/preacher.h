#pragma once
#include "BuildingDeck.h"
#include "player_card.h"


class Preacher : public CharacterCard
{
public:
	Preacher();

	void ability() const noexcept override;

	void build_building(const std::shared_ptr<BuildingCard>& card) const noexcept override;
};
