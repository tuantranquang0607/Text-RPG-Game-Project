#pragma once

#include "IState.h"
#include "../Selector.h"

class Console;
class Keyboard;
class StateMachine;

// Declare the GameState class, which inherits from the IState interface.
class GameState : public IState
{
private:
	// References to a Keyboard object and a StateMachine object.
	Console & m_Console;
	Keyboard & m_Keyboard;
	StateMachine & m_StateMachine;

	Selector <> m_Selector;

public:
	// Constructor for the GameState class. It takes references to a Keyboard object and a StateMachine object.
	GameState(Console & Console, Keyboard & keyboard, StateMachine & stateMachine);
	// Destructor for the GameState class.
	~GameState();

	// Method to be called when entering the GameState. Overrides the corresponding method in the IState interface.
	virtual void OnEnter() override;
	// Method to update the GameState. Overrides the corresponding method in the IState interface.
	virtual void OnExit() override;
	// Method to update the GameState. Overrides the corresponding method in the IState interface.
	virtual void Update() override;
	// Method to draw the GameState. Overrides the corresponding method in the IState interface.
	virtual void Draw() override;
	// Method to process inputs in the GameState. Overrides the corresponding method in the IState interface.
	virtual void ProcessInputs() override;

	// Method to check if the GameState should be exited. Overrides the corresponding method in the IState interface.
	virtual bool Exit() override;
};
