#include "Console.h"
#include "Logger.h"

#include <algorithm>
#include <vector>

// Function to set the text color in the console.
bool Console::SetTextColor(int size, int x, int y, HANDLE handle, WORD color)
{
	// Set the position in the console.
	COORD pos = { x, y };

	// Create a vector of color attributes.
	std::vector<WORD> write(size, color);

	// Write the color attributes to the console.
	DWORD written = 0;
	LPDWORD lpNumWritten = &written;

	if (!WriteConsoleOutputAttribute(handle, &write[0], size, pos, lpNumWritten))
	{
		// If writing the color attributes fails, log an error and return false.
		TRPG_ERROR("Failed to write the console output attribute.");
		return false;
	}

	// If writing the color attributes succeeds, return true.
	return true;
}

// Constructor for the Console class.
Console::Console() : m_pScreen(nullptr)
{
	// Initialize the screen buffer
	m_pScreen = std::make_unique<wchar_t[]>(BUFFER_SIZE);

	// Get handles to the console
	m_hConsoleWindow = GetConsoleWindow();

	// Get the dimensions of the console window.
	if (!GetWindowRect(m_hConsoleWindow, &m_ConsoleWindowRect))
	{
		// If getting the dimensions fails, throw an exception.
		throw ("Failed to get the Window Rect when creating the console.");
	}

	// Get the font size
	CONSOLE_FONT_INFO font_info;

	if (!GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font_info)) 
	{
		// If getting the font size fails, throw an exception.
		throw ("Failed to get the console font.");
	}

	COORD font_size = GetConsoleFontSize(GetStdHandle(STD_OUTPUT_HANDLE), font_info.nFont);

	/*TRPG_LOG("FONT_X: " + std::to_string(font_size.X));
	TRPG_LOG("FONT_Y: " + std::to_string(font_size.Y));*/

	// Calculate the actual size of the screen.
	int actual_screen_x = (SCREEN_WIDTH + 1) * font_size.X;
	int actual_screen_y = (SCREEN_HEIGHT + 2)* font_size.Y;

	// Calculate the position of the console window.
	int pos_x = GetSystemMetrics(SM_CXSCREEN) / 2 - (actual_screen_x / 2);
	int pos_y = GetSystemMetrics(SM_CYSCREEN) / 2 - (actual_screen_y / 2);

	// Set the size and position of the console window
	if (!MoveWindow(m_hConsoleWindow, pos_x, pos_y, actual_screen_x, actual_screen_y, TRUE))
	{
		// If setting the size and position fails, throw an exception.
		throw ("Failed to set and move the console window.");
	}

	// Clear the screen buffer
	ClearBuffer();

	// Create the screen buffer
	m_hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	if (!m_hConsole)
	{
		// If creating the screen buffer fails, throw an exception.
		throw ("Failed to create the console screen buffer.");
	}

	// Set the buffer to be active
	if (!SetConsoleActiveScreenBuffer(m_hConsole))
	{
		// If setting the active screen buffer fails, throw an exception.
		throw ("Failed to set the active screen buffer.");
	}

	// Hide the cursor
	if (!ShowConsoleCursor(false))
	{
		// If hiding the cursor fails, throw an exception.
		throw ("Failed to hide the console cursor.");
	}
}

// Destructor for the Console class.
Console::~Console()
{
}

// Function to clear the screen buffer.
void Console::ClearBuffer()
{
	// Set all the values of the buffer to an empty space
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		m_pScreen[i] = L' ';
	}

	// Reset all the buffer to white
	// SetTextColor(BUFFER_SIZE, 0, 0, m_hConsole, WHITE);
}

// Function to write text to the console.
void Console::Write(int x, int y, const std::wstring& text, WORD color)
{
	// Set the text color.
	/*SetTextColor(text.size(), x, y, m_hConsole, color);*/

	// This is a vector of invalid characters that we don't want to process.
	std::vector<wchar_t> invalidCharacters{ L' ', L'\n', L'\t', L'\r' };

	// This is a lambda function that checks if a character is equal to the first character of the text.
	// If the text is empty or has more than one character, it returns false.
	auto is_any_of = [&](wchar_t character) {
		if (text.size() > 1)
		{
			return false;
		}

		if (text.empty())
		{ 
			return true;
		}

		return character == text[0];
	};

	// This checks if none of the invalid characters are equal to the first character of the text.
	// If none of them are equal, it sets the text color.
	if (std::find_if(invalidCharacters.begin(), invalidCharacters.end(), is_any_of) == std::end(invalidCharacters))
		SetTextColor(text.size(), x, y, m_hConsole, color);

	// Calculate the position in the buffer.
	int pos = y * SCREEN_WIDTH + x;

	// Write the text to the buffer.
	swprintf(&m_pScreen[pos], BUFFER_SIZE, text.c_str());
}

// Function to draw the buffer to the console.
void Console::Draw()
{
	// Write the buffer to the console.
	WriteConsoleOutputCharacter(m_hConsole, m_pScreen.get(), BUFFER_SIZE, { 0, 0 }, &m_BytesWritten);
}

// Function to show or hide the console cursor.
bool Console::ShowConsoleCursor(bool show)
{
	// Get the cursor information.
	CONSOLE_CURSOR_INFO cursorInfo;

	if (!GetConsoleCursorInfo(m_hConsole, &cursorInfo))
	{
		// If getting the cursor information fails, log an error and return false.
		TRPG_ERROR("Failed to get the console cursor info.");
		return false;
	}

	// Set the visibility of the cursor.
	cursorInfo.bVisible = show;

	// Set the cursor information.
	return SetConsoleCursorInfo(m_hConsole, &cursorInfo);
}
