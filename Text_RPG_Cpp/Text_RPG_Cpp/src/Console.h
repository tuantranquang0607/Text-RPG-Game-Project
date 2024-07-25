#pragma once

#include "utilities/Colors.h"

#include <Windows.h>
#include <memory>
#include <string>

class Console
{
private:
	// Constants for the screen width, screen height, and buffer size.
	const int SCREEN_WIDTH = 120;
	const int SCREEN_HEIGHT = 48;
	const int BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

	const int HAL_WIDTH = SCREEN_WIDTH / 2;
	const int HAL_HEIGHT = SCREEN_HEIGHT / 2;

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

	// A private method to draw a border around the console window.
	void DrawBorder();

public:
	// The constructor for the Console class.
	Console();
	// The destructor for the Console class.
	~Console();

	const int GetScreenWidth() const 
	{ 
		return SCREEN_WIDTH; 
	}

	const int GetScreenHeight() const 
	{ 
		return SCREEN_HEIGHT; 
	}

	const int GetHalfWidth() const 
	{ 
		return HAL_WIDTH; 
	}

	const int GetHalfHeight() const 
	{ 
		return HAL_HEIGHT; 
	}

	// A public method to clear the screen buffer.
	void ClearBuffer();
	// A public method to write text to the console.
	void Write(int x, int y, const std::wstring& text, WORD color = WHITE);
	// A public method to draw the buffer to the console.
	void Draw();

	// A public method to show or hide the console cursor.
	bool ShowConsoleCursor(bool show);

	// This function draws a horizontal panel on the console.
	// It takes in the starting coordinates (x, y), the length of the panel, 
	// the color of the panel (default is WHITE), and the character to draw the panel with (default is "=").
	void DrawPanelHorz(int x, int y, size_t length, WORD color = WHITE, const std::wstring& character = L"=");

	// This function draws a vertical panel on the console.
	// It takes in the starting coordinates (x, y), the height of the panel, 
	// the color of the panel (default is WHITE), and the character to draw the panel with (default is "|").
	void DrawPanelVert(int x, int y, size_t height, WORD color = WHITE, const std::wstring& character = L"|");

	// This function draws a rectangular panel on the console.
	// It takes in the starting coordinates (x, y), the width and height of the panel, 
	// the color of the panel (default is WHITE), the character to draw the width of the panel with (default is "="),
	void DrawPanel(int x, int y, size_t width, size_t height, WORD color = WHITE, const std::wstring& width_char = L"=", const std::wstring& height_char = L"|");
};
