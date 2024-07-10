#pragma once

// Define the Button struct.
struct Button 
{
	// A boolean variable to keep track of whether the button is down.
	bool m_bIsDown;
	bool m_bIsJustPressed;
	bool m_bIsJustReleased;


	Button() : m_bIsDown{ false }, m_bIsJustPressed{ false }, m_bIsJustReleased{ false }
	{

	}

	void Update(bool pressed)
	{
		m_bIsJustPressed = !m_bIsDown && pressed;
		m_bIsJustReleased = m_bIsDown && !pressed;
		m_bIsDown = pressed;
	}
};