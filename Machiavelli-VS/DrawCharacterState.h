#pragma once
#include "State.h"

class DrawCharacterState : public State
{
public:
	DrawCharacterState();

	explicit DrawCharacterState(const std::shared_ptr<State>& old_state);

	void enter_state() override;

	void update() override;
};

