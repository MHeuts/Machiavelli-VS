#pragma once
#include <vector>
#include "BaseState.h"

class StateMachine {
private:
	std::vector<std::shared_ptr<BaseState>> stateStack;
public:
	std::shared_ptr<BaseState> CurrentState();
	void pushState(std::shared_ptr<BaseState>);
	void popState();
};
