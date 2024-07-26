#pragma once

#include <chrono>

using namespace std::chrono; // The std::chrono namespace provides functionality to deal with time.

class Timer // The Timer class is used to measure the passage of time.
{
private:
	// m_StartPoint and m_PausedPoint are time_points that represent points in time.
	// m_StartPoint is used to store the time when the timer starts.
	// m_PausedPoint is used to store the time when the timer is paused.
	time_point<steady_clock> m_StartPoint, m_PausedPoint;

	// m_bIsRunning is a boolean that indicates whether the timer is currently running.
	// m_bIsPaused is a boolean that indicates whether the timer is currently paused.
	bool m_bIsRunning, m_bIsPaused;

public:
	// The constructor and destructor for the Timer class.
	Timer();
	~Timer() = default;

	// Start() is a method that starts the timer.
	void Start();

	// Stop() is a method that stops the timer.
	void Stop();

	// Pause() is a method that pauses the timer.
	void Pause();

	// Resume() is a method that resumes the timer if it was paused.
	void Resume();

	// ElapsedMS() is a method that returns the elapsed time in milliseconds.
	const int64_t ElapsedMS();

	// ElapsedSec() is a method that returns the elapsed time in seconds.
	const int64_t ElapsedSec();

	// IsRunning() is a method that returns whether the timer is currently running.
	inline const bool IsRunning() const
	{
		return m_bIsRunning;
	}

	// IsPaused() is a method that returns whether the timer is currently paused.
	inline const bool IsPaused() const
	{
		return m_bIsPaused;
	}
};