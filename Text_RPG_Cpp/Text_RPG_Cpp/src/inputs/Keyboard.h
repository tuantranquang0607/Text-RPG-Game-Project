#pragma once

#include <string>

#include "Button.h"
#include "Keys.h"

class Keyboard
{
private:
	// An array of Button objects representing the keys on the keyboard.
	Button m_Keys[KEY_LAST];

public:
	// The constructor for the Keyboard class.
	Keyboard();
	// The destructor for the Keyboard class. Defined as default.
	~Keyboard() = default;

	// A method to update the state of the keys.
	void Update();

	// A method to handle a key press event.
	void OnKeyDown(int key);

	// A method to handle a key release event.
	void OnKeyUp(int key);

	// A method to check if a key is being held down.
	bool IsKeyHeld(int key) const;

	// A method to check if a key was just pressed.
	bool IsKeyJustPressed(int key) const;

	// A method to check if a key was just released.
	bool IsKeyJustReleased(int key) const;
};
