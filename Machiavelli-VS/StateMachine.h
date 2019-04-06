#pragma once
#include <vector>
#include "BaseState.h"


class StateMachine {
private:
	std::vector<std::shared_ptr<BaseState>> stateStack;
public:
	std::shared_ptr<BaseState> CurrentState();

	template<class T, class ...TArgs>
	void push_state(TArgs &&...args) 
	{
		stateStack.emplace_back(new T(std::forward<TArgs>(args)...));
		stateStack.back()->Enter();
	}

	void pop_state() 
	{
		stateStack.back()->Leave();
		stateStack.pop_back();
		if(stateStack.size() > 0)
			stateStack.back()->Resume();
	}

	void handle_command(const ClientCommand& command)
	{
		stateStack.back()->handle_command(command);
	}
};
