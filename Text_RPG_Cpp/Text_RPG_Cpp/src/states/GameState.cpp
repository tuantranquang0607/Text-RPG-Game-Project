#include "GameState.h"
#include "StateMachine.h"
#include "../Logger.h"
#include "../Console.h"
#include "../inputs/Keyboard.h"

// Constructor for the GameState class. Initialize m_Keyboard with the keyboard and m_StateMachine with the stateMachine passed as argument.
GameState::GameState(Console & console, Keyboard & keyboard, StateMachine& stateMachine) : 
	m_Console(console),
	m_Keyboard(keyboard), 
	m_StateMachine(stateMachine), 
	m_Selector(console, keyboard, {L"Start", L"Settings", L"Exit"})
{
}

GameState::~GameState()
{
}

// Destructor for the GameState class.
void GameState::OnEnter()
{
	// TRPG_LOG("Entered Game State");

	m_Console.ClearBuffer();
}

// Method called when entering the GameState.
void GameState::OnExit()
{
	// Log a message indicating that the game state has been exited.
	// TRPG_LOG("Exit Game State");

	m_Console.ClearBuffer();
}

// Method to update the GameState.
void GameState::Update()
{
	// Log a message indicating that the game state has been updated.
	// TRPG_LOG("Updated Game State");
}

// Method to draw the GameState.
void GameState::Draw()
{
	m_Selector.Draw();
	m_Console.Draw();
}

// Method to process inputs in the GameState.
void GameState::ProcessInputs()
{
	// If the escape key was just pressed, pop the current state from the state machine.
	if (m_Keyboard.IsKeyJustPressed(KEY_ESCAPE))
	{
		m_StateMachine.PopState();

		return;
	}

	m_Selector.ProcessInputs();
}

// Method to check if the GameState should be exited. Currently always returns false. 
bool GameState::Exit()
{
	return false;
}
