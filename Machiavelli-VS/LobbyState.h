#pragma once
#include "BaseState.h"
#include "ClientCommand.h"

class LobbyState: public BaseState
{
public:
	void handle_command(const ClientCommand& command) override;
};
