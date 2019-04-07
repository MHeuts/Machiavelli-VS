#include "pch.h"
#include "StateMachine.h"

std::shared_ptr<BaseState> StateMachine::CurrentState() {
	return stateStack.back();
}


