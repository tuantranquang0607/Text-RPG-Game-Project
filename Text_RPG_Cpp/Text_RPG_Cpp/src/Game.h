#pragma once

#include "Console.h"

class Game 
{
private:
	bool m_bIsRunning;

	std::unique_ptr<Console> m_pConsole;

	bool Init();

	void ProcessInput();
	void Update();
	void Draw();

public:
	Game();
	~Game();

	void Run();
};