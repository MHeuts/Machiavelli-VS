#pragma once
#include "State.h"

class DrawCharacterState : public State
{
public:
	DrawCharacterState() noexcept;

	explicit DrawCharacterState(const std::shared_ptr<State>& old_state) noexcept;

	void enter_state() noexcept override;

	void update() noexcept override;
};

