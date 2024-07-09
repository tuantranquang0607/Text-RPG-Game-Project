#include "Game.h"
#include "Logger.h"

#include <iostream>

bool Game::Init()
{
	m_pConsole = std::make_unique<Console>();

	return false;
}

void Game::ProcessInput()
{
	TRPG_LOG("Process Inputs\n");
}

void Game::Update()
{
	TRPG_ERROR("Update\n");
}

void Game::Draw()
{
	TRPG_LOG("Draw\n");
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
