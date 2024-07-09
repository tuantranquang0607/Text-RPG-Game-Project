#pragma once

#include "utilities/Colors.h"

#include <Windows.h>
#include <memory>
#include <string>

class Console
{
private:
	const int SCREEN_WIDTH = 120;
	const int SCREEN_HEIGHT = 48;
	const int BUFFER_SIZE = SCREEN_WIDTH * SCREEN_HEIGHT;

	HANDLE m_hConsole;
	HWND m_hConsoleWindow;
	RECT m_ConsoleWindowRect;

	std::unique_ptr<wchar_t[]> m_pScreen;

public:
	Console();
	~Console();

	void Write(int x, int y, const std::wstring& text, WORD color = WHITE);
};
