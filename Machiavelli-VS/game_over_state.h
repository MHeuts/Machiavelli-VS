#pragma once
#include "State.h"

class GameOverState: public State
{
public:
	void enter_state() override;
private:
	void showScoreScreen(const std::shared_ptr<ClientInfo> client);
	int calculateBuildingScore(const std::shared_ptr<ClientInfo> client);
	int calculateCityScore(const std::shared_ptr<ClientInfo> client);
	int calculateColorScore(const std::shared_ptr<ClientInfo> client);
};
