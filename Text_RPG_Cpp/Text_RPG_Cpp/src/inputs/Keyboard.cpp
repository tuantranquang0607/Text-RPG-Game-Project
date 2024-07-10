#include "Keyboard.h"
#include "../Logger.h"

// Constructor for the Keyboard class.
Keyboard::Keyboard()
{
	// Nothing to do here
}

// Method to update the state of the keys.
void Keyboard::Update()
{
	// Loop through all keys and reset their just pressed and just released states.
	for (int i = 0; i < KEY_LAST; i++)
	{
		m_Keys[i].m_bIsJustPressed = false;
		m_Keys[i].m_bIsJustReleased = false;
	}
}

// Method to handle a key press event.
void Keyboard::OnKeyDown(int key)
{
	// CHeck to see if the key is defined.
	if (key > KEY_LAST) 
	{
		// If the key code is invalid, log an error and return.
		TRPG_ERROR("[" + std::to_string(key) + "] is not defined.");

		return;
	}

	// If the key code is valid, update the key's state to pressed.
	m_Keys[key].Update(true);
}

// Method to handle a key release event.
void Keyboard::OnKeyUp(int key)
{
	// CHeck to see if the key is defined.
	if (key > KEY_LAST) 
	{
		// If the key code is invalid, log an error and return.
		TRPG_ERROR("[" + std::to_string(key) + "] is not defined.");

		return;
	}

	// If the key code is valid, update the key's state to not pressed.
	m_Keys[key].Update(false);
}

// Method to check if a key is being held down.
bool Keyboard::IsKeyHeld(int key) const
{
	// CHeck to see if the key is defined.
	if (key > KEY_LAST) 
	{
		// If the key code is invalid, log an error and return false.
		TRPG_ERROR("[" + std::to_string(key) + "] is not defined.");

		return false;
	}

	// If the key code is valid, return whether the key is being held down.
	return m_Keys[key].m_bIsDown;
}

// Method to check if a key was just pressed.
bool Keyboard::IsKeyJustPressed(int key) const
{
	// CHeck to see if the key is defined.
	if (key > KEY_LAST) 
	{
		// If the key code is invalid, log an error and return false.
		TRPG_ERROR("[" + std::to_string(key) + "] is not defined.");

		return false;
	}

	// If the key code is valid, return whether the key was just pressed.
	return m_Keys[key].m_bIsJustPressed;
}

// Method to check if a key was just released.
bool Keyboard::IsKeyJustReleased(int key) const
{
	// CHeck to see if the key is defined.
	if (key >= KEY_LAST) 
	{
		// If the key code is invalid, log an error and return false.
		TRPG_ERROR("[" + std::to_string(key) + "] - Is not defined!");

		return false;
	}

	// If the key code is valid, return whether the key was just released.
	return m_Keys[key].m_bIsJustReleased;
}
