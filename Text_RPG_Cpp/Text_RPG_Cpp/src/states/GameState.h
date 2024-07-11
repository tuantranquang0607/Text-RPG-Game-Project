#pragma once

#include "IState.h"

class Keyboard;
class StateMachine;

class GameState : public IState
{
private:
	Keyboard & m_Keyboard;
	StateMachine & m_StateMachine;

public:
	GameState(Keyboard & keyboard, StateMachine & stateMachine);
	~GameState();

	virtual void OnEnter() override;
	virtual void OnExit() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual void ProcessInputs() override;

	virtual bool Exit() override;
};
