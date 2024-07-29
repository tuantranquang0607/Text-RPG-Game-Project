#pragma once

#include <memory>
#include <string>

#include "Timer.h"	

class TRPG_Globals
{
private:
	int m_GameTime, m_SavedGameTime; // Game time and saved game time

	Timer m_Timer; // Timer object

	TRPG_Globals(); // Private constructor (for Singleton pattern)

	static std::unique_ptr<TRPG_Globals> m_pInstance; // Static unique_ptr for the Singleton instance

public:
	static TRPG_Globals& GetInstance(); // Static method to get the Singleton instance

	// Getter for the game time
	const int GetGameTime() const
	{
		return m_GameTime;
	}

	// Setter for the saved game time
	void SetSaveGameTime(int save_time)
	{
		m_SavedGameTime = save_time;
	}

	void Update(); // Method to update the game state

	const std::wstring GetTime(); // Method to get the game time as a string
};
