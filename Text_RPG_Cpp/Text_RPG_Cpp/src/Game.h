#pragma once

#include "Console.h"

// Declare the Game class.
class Game 
{
private:
	// A boolean variable to keep track of whether the game is running.
	bool m_bIsRunning;

	// A unique pointer to a Console object. This represents the console where the game is displayed.
	std::unique_ptr<Console> m_pConsole;

	// A private method to initialize the game. Returns true if initialization is successful, false otherwise.
	bool Init();

	// A private method to process player input.
	void ProcessInput();

	// A private method to update the game state.
	void Update();

	// A private method to draw the game state.
	void Draw();

public:
	// The constructor for the Game class.
	Game();

	// The destructor for the Game class.
	~Game();

	// A public method to run the game.
	void Run();
};