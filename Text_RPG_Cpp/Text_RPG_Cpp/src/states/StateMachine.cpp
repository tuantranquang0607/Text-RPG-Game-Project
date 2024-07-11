#include "StateMachine.h"

// Constructor for the StateMachine class.
StateMachine::StateMachine() : m_States()
{
}

// Destructor for the StateMachine class.
StateMachine::~StateMachine()
{
}

// Method to push a new state onto the stack.
void StateMachine::PushState(StatePtr newState)
{
	// Push the new state onto the stack.
	m_States.push(std::move(newState));
	// Call the OnEnter method of the new state.
	m_States.top()->OnEnter();
}

// Method to pop a state from the stack.
StatePtr StateMachine::PopState()
{
	// If the stack is empty, return nullptr.
	if (m_States.empty())
	{
		return nullptr;
	}

	// Get the top state from the stack.
	auto oldState = std::move(m_States.top());

	// Remove the top state from the stack.
	m_States.pop();

	// Call the OnExit method of the old state.
	oldState->OnExit();

	// Return the old state.
	return oldState;
}

// Method to get the current state (the state on top of the stack).
StatePtr& StateMachine::GetCurrentState()
{
	// Return the top state from the stack.
	return m_States.top();
}
