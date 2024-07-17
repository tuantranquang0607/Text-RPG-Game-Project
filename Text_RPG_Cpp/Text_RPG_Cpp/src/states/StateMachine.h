#pragma once

#include <memory>
#include <stack>

#include "IState.h"

// Define a type alias for a unique pointer to an IState object.
typedef std::unique_ptr<IState> StatePtr;

class StateMachine
{
private:
	// A stack of unique pointers to IState objects. This represents the states of the state machine.
	std::stack<StatePtr> m_States;

public:
	// The constructor for the StateMachine class.
	StateMachine();
	// The destructor for the StateMachine class.
	~StateMachine();

	// A method to push a new state onto the stack.
	void PushState(StatePtr newState);

	// A method to pop a state from the stack.
	StatePtr PopState();

	// A method to check if the stack is empty.
	const bool Empty() const 
	{ 
		return m_States.empty(); 
	}

	// A method to get the current state (the state on top of the stack).
	StatePtr& GetCurrentState();
};