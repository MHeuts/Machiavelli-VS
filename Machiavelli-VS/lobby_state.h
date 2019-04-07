#pragma once
#include "State.h"


class LobbyState : public State
{
public:
	LobbyState();

	explicit LobbyState(const std::shared_ptr<State>& old_state);

	void render(std::shared_ptr<ClientInfo>& client) override;

	void update() override;
};
