#pragma once

class Game 
{
private:
	bool m_bIsRunning;

	bool Init();

	void ProcessInput();
	void Update();
	void Draw();

public:
	Game();
	~Game();

	void Run();
};