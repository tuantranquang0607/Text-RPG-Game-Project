#pragma once

#include "utilities/Colors.h"

#include <Windows.h>
#include <memory>
#include <string>

// Declare the Console class.
class Console
{
private:
	// Constants for the screen width, screen height, and buffer size.
	const int SCREEN_WIDTH = 120;
	const int SCREEN_HEIGHT = 48;
	const int BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

	// Handles to the console and console window.
	HANDLE m_hConsole;
	HWND m_hConsoleWindow;

	// A RECT structure that defines the dimensions of the console window.
	RECT m_ConsoleWindowRect;

	// The number of characters written to the console.
	DWORD m_BytesWritten;

	// A unique pointer to a wide character array. This represents the screen buffer.
	std::unique_ptr<wchar_t[]> m_pScreen;

	// A private method to set the text color in the console.
	bool SetTextColor(int size, int x, int y, HANDLE handle, WORD color);

public:
	// The constructor for the Console class.
	Console();

	// The destructor for the Console class.
	~Console();

	// A public method to clear the screen buffer.
	void ClearBuffer();

	// A public method to write text to the console.
	void Write(int x, int y, const std::wstring& text, WORD color = WHITE);

	// A public method to draw the buffer to the console.
	void Draw();

	// A public method to show or hide the console cursor.
	bool ShowConsoleCursor(bool show);
};
