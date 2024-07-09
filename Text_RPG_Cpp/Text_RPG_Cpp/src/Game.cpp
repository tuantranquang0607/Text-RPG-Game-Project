#include "Game.h"
#include "Logger.h"

#include <iostream>

bool Game::Init()
{
	try 
	{
		m_pConsole = std::make_unique<Console>();
	}
	catch (const std::exception& e)
	{
		std::string error = e.what();
		TRPG_ERROR(error);
		return false;
	}

	/*m_pConsole = std::make_unique<Console>();*/

	return true;
}

void Game::ProcessInput()
{
	/*TRPG_LOG("Process Inputs\n");*/
}

void Game::Update()
{
	/*TRPG_ERROR("Update\n");*/
}

void Game::Draw()
{
	/*TRPG_LOG("Draw\n");*/

	m_pConsole->Write(10, 10, L"Hello World!!!", RED);
	m_pConsole->Draw();
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
