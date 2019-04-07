#pragma once
#include "player_card.h"

class Merchant : public CharacterCard
{
public:
	Merchant();

	void ability() const noexcept override;

	int bonus() const noexcept override;
};
