#include "pch.h"
#include "StateMachine.h"

std::unique_ptr<BaseState> StateMachine::CurrentState() {
	//return std::make_unique<BaseState>(stateStack.back());
}

void StateMachine::popState() {
	if(stateStack.size()>1) {
		stateStack.pop_back();
	}
}

void StateMachine::pushState(std::unique_ptr<BaseState> state) {
	stateStack.push_back(state);
}

