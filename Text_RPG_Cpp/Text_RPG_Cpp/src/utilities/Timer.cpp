#include "Timer.h"

// The constructor for the Timer class. It initializes the timer to not be running or paused.
Timer::Timer() : m_bIsRunning{ false }, m_bIsPaused{ false }
{
}

// The Start() method starts the timer by setting the start point to the current time and setting the running flag to true.
void Timer::Start()
{
	if (!m_bIsRunning)
	{
		m_StartPoint = steady_clock::now();
		m_bIsRunning = true;
		m_bIsPaused = false;
	}
}

// The Stop() method stops the timer by setting the running flag to false.
void Timer::Stop()
{
	if (m_bIsRunning)
	{
		m_bIsRunning = false;
	}
}

// The Pause() method pauses the timer by setting the paused point to the current time and setting the paused flag to true.
void Timer::Pause()
{
	if (m_bIsRunning && !m_bIsPaused)
	{
		m_PausedPoint = steady_clock::now();
		m_bIsPaused = true;
	}
}

// The Resume() method resumes the timer by adjusting the start point to account for the paused duration and setting the paused flag to false.
void Timer::Resume()
{
	if (m_bIsRunning && m_bIsPaused)
	{
		m_StartPoint += duration_cast<milliseconds>(steady_clock::now() - m_PausedPoint);
		m_bIsPaused = false;
	}
}

// The ElapsedMS() method returns the elapsed time in milliseconds. If the timer is paused, it returns the time up to when it was paused. If the timer is running, it returns the time up to the current moment.
const int64_t Timer::ElapsedMS()
{
	if (m_bIsRunning)
	{
		if (m_bIsPaused)
		{
			return duration_cast<milliseconds>(m_PausedPoint - m_StartPoint).count();
		}
		else
		{
			return duration_cast<milliseconds>(steady_clock::now() - m_StartPoint).count();
		}
	}

	return 0;
}

// The ElapsedSec() method returns the elapsed time in seconds by calling the ElapsedMS() method and dividing the result by 1000.
const int64_t Timer::ElapsedSec()
{
	return ElapsedMS() / 1000;
}
