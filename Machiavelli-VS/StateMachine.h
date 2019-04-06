#pragma once
#include <vector>
#include "BaseState.h"

class StateMachine {
private:
	std::vector<std::shared_ptr<BaseState>> stateStack;
public:
	std::shared_ptr<BaseState> CurrentState();
	void pushState(std::shared_ptr<BaseState>);

	template<class T, class ...TArgs>
	void push_state(TArgs &&...args) 
	{

		stateStack.push_back(new T(std::forward<TArgs>(args)...));
		stateStack.back()->Enter();
	}

	void pop_state() 
	{
		stateStack.back()->Leave();
		stateStack.pop_back();
		stateStack.back()->Resume();
	}

	void handle_command(ClientCommand& command)
	{
		stateStack.back()->handle_command(command);
	}
};
