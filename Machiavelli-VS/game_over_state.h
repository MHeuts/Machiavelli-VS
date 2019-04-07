#pragma once
#include "State.h"

class GameOverState: public State
{
public:
	void enter_state() override;
private:
	void showScoreScreen(std::shared_ptr<ClientInfo> client);
	int calculateBuildingScore(std::shared_ptr<ClientInfo> client);
	int calculateCityScore(std::shared_ptr<ClientInfo> client);
	int calculateColorScore(std::shared_ptr<ClientInfo> client);
};
