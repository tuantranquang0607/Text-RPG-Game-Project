#pragma once

#include "Console.h"
#include "inputs/Keyboard.h"

// Declare the Game class.
class Game 
{
private:
	// A boolean variable to keep track of whether the game is running.
	bool m_bIsRunning;

	// A unique pointer to a Console object. This represents the console where the game is displayed.
	std::unique_ptr<Console> m_pConsole;

	// A unique pointer to a Keyboard object. This represents the keyboard input for the game.
	std::unique_ptr<Keyboard> m_pKeyboard;

	// A DWORD variable to keep track of the number of events read from the console input.
	DWORD m_NumRead;
	
	// An array of INPUT_RECORD structures to store the input records read from the console input.
	INPUT_RECORD m_InRecBuf[128];

	// A HANDLE variable to store the handle to the console input.
	HANDLE m_hConsoleIn;

	// A private method to initialize the game. Returns true if initialization is successful, false otherwise.
	bool Init();

	// A private method to process events such as player input.
	void ProcessEvents();

	// A private method to process player input.
	void ProcessInputs();

	// A private method to update the game state.
	void Update();

	// A private method to draw the game state.
	void Draw();

	// A private method to handle key events.
	void KeyEventProcess(KEY_EVENT_RECORD keyEvent);

public:
	// The constructor for the Game class.
	Game();

	// The destructor for the Game class.
	~Game();

	// A public method to run the game.
	void Run();
};