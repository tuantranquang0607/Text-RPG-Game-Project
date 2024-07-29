#include "Game.h"
#include "Logger.h"
#include "states/GameState.h"
#include "utilities/Globals.h"

#include <iostream>

// Initialize the game.
bool Game::Init()
{
	try 
	{
		// Try to create a new Console object.
		m_pConsole = std::make_unique<Console>();
	}
	catch (const std::exception& e)
	{
		// If an exception is thrown, log the error and return false.
		std::string error = e.what();
		TRPG_ERROR(error);
		return false;
	}

	/*m_pConsole = std::make_unique<Console>();*/

	// Get the handle to the console input.
	m_hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);

	// Create a unique_ptr to a new Keyboard object.
	m_pKeyboard = std::make_unique<Keyboard>();

	// Create a unique_ptr to a new StateMachine object.
	m_pStateMachine = std::make_unique<StateMachine>();

	// Push a new GameState onto the state machine.
	m_pStateMachine->PushState(std::make_unique<GameState>(*m_pConsole, *m_pKeyboard, *m_pStateMachine));

	// If no exceptions are thrown, return true.
	return true;
}

// Process events such as player input.
void Game::ProcessEvents()
{
	// Geth the number of console inputs.
	if (!GetNumberOfConsoleInputEvents(m_hConsoleIn, &m_NumRead)) 
	{
		// If getting the number of console input events fails, log an error.
		DWORD error = GetLastError();

		TRPG_ERROR("Failed to get the number of console input events. Error code: " + std::to_string(error));

		return;
	}

	// If there are no console input events, return.
	if (m_NumRead <= 0)
	{
		return;
	}

	// Peek at the console input.
	if (!PeekConsoleInput(m_hConsoleIn, m_InRecBuf, 128, &m_NumRead))
	{
		// If peeking at the console input fails, log an error.
		DWORD error = GetLastError();

		TRPG_ERROR("Failed to peek events, Error code: " + error);

		return;
	}

	// Read the console input.
	for (int i = 0; i < m_NumRead; i++)
	{
		// Switch on the event type.
		switch (m_InRecBuf[i].EventType) 
		{
			case KEY_EVENT:
				KeyEventProcess(m_InRecBuf[i].Event.KeyEvent);

				break;

			default:
				break;
		}
	}

	// Clear or Flush other input events.
	FlushConsoleInputBuffer(m_hConsoleIn);
}

// Process player input. 
void Game::ProcessInputs()
{
	/*TRPG_LOG("Process Inputs\n");*/

	// If the escape key is pressed, set m_bIsRunning to false.
	if (m_pKeyboard->IsKeyJustPressed(KEY_ESCAPE))
	{
		m_bIsRunning = false;
	}

	if (m_pStateMachine->Empty())
	{
		TRPG_ERROR("No state in the state machine to process inputs.");

		m_bIsRunning = false;

		return;
	}

	m_pStateMachine->GetCurrentState()->ProcessInputs();
}

// Update the game state. 
void Game::Update()
{
	// If there is no current state in the state machine, log an error and set m_bIsRunning to false.
	if (m_pStateMachine->Empty()) 
	{
		TRPG_ERROR("No state in the state machine to update.");

		m_bIsRunning = false;

		return;
	}

	// Update the current state.
	m_pStateMachine->GetCurrentState()->Update();

	// Update the keyboard.
	m_pKeyboard->Update();

	// Update the global game time.
	TRPG_Globals::GetInstance().Update();
}

// Draw the game state.
void Game::Draw()
{
	/*TRPG_LOG("Draw\n");*/

	// Write "Hello World!!!" in red at position (10, 10) on the console.
	// m_pConsole->Write(10, 10, L"Hello World!!!", RED);

	// If there is no current state in the state machine, log an error and set m_bIsRunning to false.
	if (m_pStateMachine->Empty()) 
	{
		TRPG_ERROR("No state in the state machine to draw.");

		m_bIsRunning = false;

		return;
	}

	// Clear the console.
	m_pStateMachine->GetCurrentState()->Draw();

	// Draw the console.
	m_pConsole->Draw();
}

// Handle key events.
void Game::KeyEventProcess(KEY_EVENT_RECORD keyEvent)
{
	// If the key event is key down, call OnKeyDown. Otherwise, call OnKeyUp.
	if (keyEvent.bKeyDown)
	{
		m_pKeyboard->OnKeyDown(keyEvent.wVirtualKeyCode);
	}
	else
	{
		m_pKeyboard->OnKeyUp(keyEvent.wVirtualKeyCode);
	}
}

// Constructor for the Game class and initialize member variables in the initializer list.
Game::Game(): m_bIsRunning(true), m_pKeyboard(nullptr), m_pConsole(nullptr), m_pStateMachine(nullptr)
{

}

// Destructor for the Game class.
Game::~Game()
{

}

// Run the game.
void Game::Run()
{
	// If the game fails to initialize, set m_bIsRunning to false.
	if (!Init())
	{
		m_bIsRunning = false;
	}

	// While the game is running, process input, process events, update the game state, and draw the game state.
	while (m_bIsRunning)
	{
		ProcessEvents();
		ProcessInputs();
		Update();
		Draw();
	}

	// When the game ends, output "Bye Bye\n".
	std::cout << "Bye Bye\n";
}
