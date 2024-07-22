#include "GameState.h"
#include "StateMachine.h"
#include "../Logger.h"
#include "../Console.h"
#include "../inputs/Keyboard.h"

// This is the constructor for the GameState class. It initializes the class with a Console, Keyboard, and StateMachine.
// It also initializes the Selector with the Console, Keyboard, and a vector of options.
// Finally, it creates a new Player object with the name "Test Player", level 1, and 200 health points, 
// and assigns it to the unique_ptr m_TestPlayer.
GameState::GameState(Console& console, Keyboard& keyboard, StateMachine& stateMachine) :
	m_Console(console), // Initialize the Console reference
	m_Keyboard(keyboard), // Initialize the Keyboard reference
	m_StateMachine(stateMachine), // Initialize the StateMachine reference
	m_Selector(console, keyboard, { L"Start", L"Settings", L"Exit" }), // Initialize the Selector
	m_TestInventory{} // Test to be removed
{
	// Create a new Player object and assign it to m_TestPlayer
	m_TestPlayer = std::make_unique<Player>(L"Test Player", L"text-player", m_TestInventory, 1, 200);
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

// This function is responsible for drawing the game state on the console.
void GameState::Draw()
{
	// Get the name of the test player.
	const auto& name = m_TestPlayer->GetName();

	// Convert the current health points of the test player to a string.
	std::wstring hp = std::to_wstring(m_TestPlayer->GetHP());

	// Convert the maximum health points of the test player to a string.
	std::wstring max_hp = std::to_wstring(m_TestPlayer->GetMaxHP());

	// Write the name of the test player on the console at position (50, 30) in blue color.
	m_Console.Write(50, 30, name, BLUE);

	// Write the current and maximum health points of the test player on the console at position (50, 32) in blue color.
	m_Console.Write(50, 32, L"HP: " + hp + L"/" + max_hp, BLUE);

	// Draw the selector.
	m_Selector.Draw();

	// Draw the console.
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
