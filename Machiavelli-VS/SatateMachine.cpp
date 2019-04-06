#include "pch.h"
#include "StateMachine.h"

std::shared_ptr<BaseState> StateMachine::CurrentState() {
	return stateStack.back();
}

void StateMachine::popState() {
	if(stateStack.size()>1) {
		stateStack.pop_back();
	}
}

void StateMachine::pushState(std::shared_ptr<BaseState> state) {
	stateStack.push_back(state);
}

