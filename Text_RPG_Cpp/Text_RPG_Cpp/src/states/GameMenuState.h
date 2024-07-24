#pragma once

#include "IState.h"

class Party;
class Console;
class StateMachine;
class Keyboard;

// GameMenuState class is a derived class of IState (a base class representing a state).
class GameMenuState : public IState
{
private:
	// References to Party, Console, StateMachine, and Keyboard objects.
	Party& m_Party;
	Console& m_Console;
	StateMachine& m_StateMachine;
	Keyboard& m_Keyboard;

public:
	// Constructor that initializes references to Party, Console, StateMachine, and Keyboard. Destructor
	GameMenuState(Party& party, Console& console, StateMachine& stateMachine, Keyboard& keyboard);
	~GameMenuState();

	// Virtual functions from IState that are overridden in GameMenuState.
	virtual void OnEnter() override; // Called when entering the state.
	virtual void OnExit() override; // Called when exiting the state.
	virtual void Update() override; // Called every frame to update the state.
	virtual void Draw() override; // Called every frame to draw the state.
	virtual void ProcessInputs() override; // Called to process inputs in the state.

	virtual bool Exit() override; // Called to exit the state.
};
