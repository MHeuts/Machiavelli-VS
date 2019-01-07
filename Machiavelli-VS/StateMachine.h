#pragma once
#include <vector>
#include "BaseState.h"

class StateMachine {
private:
	std::vector<std::unique_ptr<BaseState>> stateStack;
public:
	std::unique_ptr<BaseState> CurrentState();
	void pushState(std::unique_ptr<BaseState>);
	void popState();
};
