#pragma once

#include <memory>
#include <string>

#include "Timer.h"	

class TRPG_Globals
{
private:
	int m_GameTime, m_SavedGameTime;

	Timer m_Timer;

	TRPG_Globals();

	static std::unique_ptr<TRPG_Globals> m_pInstance;

public:
	static TRPG_Globals& GetInstance();

	const int GetGameTime() const
	{
		return m_GameTime;
	}

	void SetSaveGameTime(int save_time)
	{
		m_SavedGameTime = save_time;
	}

	void Update();

	const std::wstring GetTime();
};
