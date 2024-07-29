#include "Globals.h"
#include "trpg_utilities.h"

// Initialize the static unique_ptr member variable to nullptr
std::unique_ptr<TRPG_Globals> TRPG_Globals::m_pInstance = nullptr;

// Constructor: Initializes game time, saved game time, and starts the timer
TRPG_Globals::TRPG_Globals() : m_GameTime(0), m_SavedGameTime(0), m_Timer()
{
	m_Timer.Start();
}

// Singleton pattern: Returns the instance of TRPG_Globals
TRPG_Globals& TRPG_Globals::GetInstance()
{
    if (!m_pInstance) // If the instance doesn't exist
	{
		m_pInstance.reset(new TRPG_Globals()); // Create a new instance
	}

	return *m_pInstance; // Return the instance
}

// Update the game time with the elapsed time from the timer
void TRPG_Globals::Update()
{
	m_GameTime = m_Timer.ElapsedSec() + m_SavedGameTime;
}

// Get the current game time in the format of hours:minutes:seconds
const std::wstring TRPG_Globals::GetTime()
{
	int hours = m_GameTime / 3600;
	int minutes = (m_GameTime % 3600) / 60;
	int seconds = m_GameTime % 60;

	std::wstring time
	{
		PadNumbers(hours) + L":" + PadNumbers(minutes) + L":" + PadNumbers(seconds)
	};

    return time;
}
