#pragma once
#include "BaseState.h"

class DrawCharacterState: public BaseState
{
public:
	void Enter() override;
	void handle_command(const ClientCommand& command) override;
};