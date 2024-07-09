#include "Console.h"
#include "Logger.h"

Console::Console() : m_pScreen(nullptr)
{
	// Initialize the screen buffer
	m_pScreen = std::make_unique<wchar_t[]>(BUFFER_SIZE);

	// Get handles to the console
	m_hConsoleWindow = GetConsoleWindow();

	if (!GetWindowRect(m_hConsoleWindow, &m_ConsoleWindowRect))
	{
		throw ("Failed to get the Window Rect when creating the console.");
	}

	// Get the font size
	CONSOLE_FONT_INFO font_info;

	if (!GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font_info)) 
	{
		throw ("Failed to get the console font.");
	}

	COORD font_size = GetConsoleFontSize(GetStdHandle(STD_OUTPUT_HANDLE), font_info.nFont);

	TRPG_LOG("FONT_X: " + std::to_string(font_size.X));
	TRPG_LOG("FONT_Y: " + std::to_string(font_size.Y));
}

Console::~Console()
{
}

void Console::Write(int x, int y, const std::wstring& text, WORD color)
{
}
