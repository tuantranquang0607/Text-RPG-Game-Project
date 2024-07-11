#pragma once

class IState
{
public:
	// Virtual destructor. It's empty but can be overridden by derived classes.
	virtual ~IState() {};

	// Pure virtual method to be called when entering a state. Must be implemented by derived classes.
	virtual void OnEnter() = 0;
	// Pure virtual method to be called when exiting a state. Must be implemented by derived classes.
	virtual void OnExit() = 0;
	// Pure virtual method to update a state. Must be implemented by derived classes.
	virtual void Update() = 0;
	// Pure virtual method to draw a state. Must be implemented by derived classes.
	virtual void Draw() = 0;
	// Pure virtual method to process inputs in a state. Must be implemented by derived classes.
	virtual void ProcessInputs() = 0;

	// Pure virtual method to check if a state should be exited. Must be implemented by derived classes.
	virtual bool Exit() = 0;
};