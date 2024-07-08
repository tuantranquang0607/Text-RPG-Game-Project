#include "Game.h"

#include <iostream>

bool Game::Init()
{
	return true;
}

void Game::ProcessInput()
{
	std::cout << "Process Inputs\n";
}

void Game::Update()
{
	std::cout << "Update\n";
}

void Game::Draw()
{
	std::cout << "Draw\n";
}

Game::Game(): m_bIsRunning(true)
{

}

Game::~Game()
{
}

void Game::Run()
{
	if (!Init())
	{
		m_bIsRunning = false;
	}

	while (m_bIsRunning)
	{
		ProcessInput();
		Update();
		Draw();
	}

	std::cout << "Bye Bye\n";
}
