#pragma once

#include <memory>

#include "IState.h"
#include "../Selector.h"
#include "../Player.h"

class Console;
class Keyboard;
class StateMachine;

// Declare the GameState class, which inherits from the IState interface.
class GameState : public IState
{
private:
	// Reference to a Console object.
	Console & m_Console;

	// Reference to a Keyboard object.
	Keyboard & m_Keyboard;

	// Reference to a StateMachine object.
	StateMachine & m_StateMachine;

	// An instance of the Selector class. The template parameters are not specified here, 
	// which might be a typo or the class could be using default template parameters.
	Selector <> m_Selector;

	std::unique_ptr<Player> m_TestPlayer;

public:
	// This is the constructor for the GameState class. It initializes the class with a Console, Keyboard, and StateMachine.
	GameState(Console & Console, Keyboard & keyboard, StateMachine & stateMachine);

	// This is the destructor for the GameState class. It's called when an object of the class is destroyed.
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
