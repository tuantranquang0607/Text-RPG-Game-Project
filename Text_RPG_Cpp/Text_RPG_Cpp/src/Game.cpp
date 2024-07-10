#include "Game.h"
#include "Logger.h"

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

	// If no exceptions are thrown, return true.
	return true;
}

// Process player input. 
void Game::ProcessInput()
{
	/*TRPG_LOG("Process Inputs\n");*/
}

// Update the game state. 
void Game::Update()
{
	/*TRPG_ERROR("Update\n");*/
}

// Draw the game state.
void Game::Draw()
{
	/*TRPG_LOG("Draw\n");*/

	// Write "Hello World!!!" in red at position (10, 10) on the console.
	m_pConsole->Write(10, 10, L"Hello World!!!", RED);

	// Draw the console.
	m_pConsole->Draw();
}

// Constructor for the Game class. Initializes m_bIsRunning to true.
Game::Game(): m_bIsRunning(true)
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

	// While the game is running, process input, update the game state, and draw the game state.
	while (m_bIsRunning)
	{
		ProcessInput();
		Update();
		Draw();
	}

	// When the game ends, output "Bye Bye\n".
	std::cout << "Bye Bye\n";
}
