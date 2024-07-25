#pragma once

#define NOMINMAX // Define NOMINMAX to avoid conflicts with the min and max macros in the Windows headers.

#include <functional> // Include the functional header for function objects and operations.
#include <algorithm>
#include <vector>
#include <string>
#include <type_traits> // Include the type_traits header for type inspections and transformations.

#include "Console.h"
#include "inputs/Keyboard.h"
#include "Logger.h"

struct SelectorParams
{
	// Member variables for the selector parameters.
	int x, y, columns, currentX, currentY, spacingX, spacingY;
	std::wstring cursor;

	// Constructor for the SelectorParams struct with default values. Initialize member variables with the values passed to the constructor.
	SelectorParams (int x = 20, int y = 10, int columns = 1, int current_x =  0, int current_y = 0, int spacing_x = 20, int spacing_y = 5, std::wstring cursor = L"->")
	{
		this->x = x;
		this->y = y;
		this->columns = columns;
		this->currentX = current_x;
		this->currentY = current_y;
		this->spacingX = spacing_x;
		this->spacingY = spacing_y;
		this->cursor = cursor;
	}
};

// Declare the Selector class template.
template <typename T = std::wstring> class Selector
{
private:
	// Member variables for the Selector class.
	Console& m_Console;
	Keyboard& m_Keyboard;

	std::function<void(int, std::vector<T>)> m_OnSelection;
	std::function<void(int, int, T)> m_OnDrawItems;
	std::vector<T> m_Data;

	SelectorParams m_Params;

	bool m_bShowCursor;

	int m_Rows;

	// This function is used to move the cursor or selection up.
	void MoveUp();

	// This function is used to move the cursor or selection down.
	void MoveDown();

	// This function is used to move the cursor or selection to the left.
	void MoveLeft();

	// This function is used to move the cursor or selection to the right.
	void MoveRight();

	// This function is triggered when an action is performed, such as pressing a button.
	void OnAction();

	// This function is used to draw an item at a specific position (x, y).
	// The item to be drawn is of type T.
	void DrawItem(int x, int y, T item);

	// This function is triggered when a selection is made from a list of data.
	// The selected item's index and the data list are passed as arguments.
	void OnSelection(int index, std::vector<T> data);

public:
	// Constructors and destructor for the Selector class.
	Selector(Console& console, Keyboard& keyboard, std::vector<T> data, SelectorParams params = SelectorParams());
	Selector(Console& console, 
			 Keyboard& keyboard, 
			 std::function<void(int, std::vector<T>)> on_selection, 
			 std::function<void(int, int, T)> on_draw_item, 
			 std::vector<T> data, 
			 SelectorParams params = SelectorParams());
	~Selector();

	// Method to set the data for the selector.
	void SetData(std::vector<T> data) 
	{ 
		m_Data = data;
	};

	// Method to get the data for the selector.
	/*const std::vector<T>& GetData() 
	{ 
		return m_Data; 
	};*/

	// Method to set the selection function for the selector.
	void SetSelectionFunc(std::function<void(int, std::vector<T>)> on_selection) 
	{ 
		m_OnSelection = on_selection; 
	};

	// Method to set the draw function for the selector.
	void SetDrawFunc(std::function<void(int, int, T)> on_draw_item) 
	{ 
		m_OnDrawItems = on_draw_item; 
	};

	// Method to show the cursor.
	void ShowCursor() 
	{ 
		m_bShowCursor = true; 
	};

	// Method to hide the cursor.
	void HideCursor() 
	{ 
		m_bShowCursor = false; 
	};

	// Method to get the index of the current selection.
	const int GetIndex() 
	{ 
		return m_Params.currentX + (m_Params.currentY * m_Params.columns); 
	};

	// This function is responsible for processing user inputs.
	void ProcessInputs();

	// This function is used to draw or render the entire screen or a specific component.
	void Draw();
};

// This is a constructor for the Selector class. It initializes the class with a console, keyboard, data, and parameters.
// It also sets the OnSelection and DrawItem functions to the class's own methods.
template<typename T>
inline Selector<T>::Selector(Console& console, Keyboard& keyboard, std::vector<T> data, SelectorParams params)
	: Selector(console, 
			   keyboard, 
			   [this](int index, std::vector<T> data) { Selector::OnSelection(index, data); },
			   [this](int x, int y, T item) { Selector::DrawItem(x, y, item); },
			   data, 
			   params)
{

}

// This is another constructor for the Selector class. It initializes the class with a console, keyboard, data, and parameters.
// It also sets the OnSelection and DrawItem functions to the provided functions.
template<typename T>
inline Selector<T>::Selector(Console& console,
							 Keyboard& keyboard, 
							 std::function<void(int, std::vector<T>)> on_selection, 
							 std::function<void(int, int, T)> on_draw_item, 
							 std::vector<T> data, 
							 SelectorParams params )
	: m_Console(console), 
	m_Keyboard(keyboard), 
	m_OnSelection(on_selection), 
	m_OnDrawItems(on_draw_item), 
	m_Data(data), 
	m_Params(params), 
	m_bShowCursor(true)
{
	// Initialize the rows member variable by dividing the size of the data by the number of columns.
	m_Rows = std::ceil(m_Data.size() / (params.columns == 0 ? 1 : params.columns));

	// Check to see if rows is < 1.
	if (m_Rows < 1) 
	{
		// Set rows to 1.
		m_Rows = 1;
	}
}

// This is the destructor for the Selector class. It doesn't do anything in this case.
template<typename T>
inline Selector<T>::~Selector()
{

}

// This function processes the inputs from the keyboard.
template<typename T>
inline void Selector<T>::ProcessInputs()
{
	if (m_Keyboard.IsKeyJustPressed(KEY_W)) 
	{
		MoveUp();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_S)) 
	{
		MoveDown();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_A)) 
	{
		MoveLeft();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_D))
	{
		MoveRight();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_SPACE)) 
	{
		OnAction();
	}
}

// These functions move the current selection up, down, left, or right.
template<typename T>
inline void Selector<T>::MoveUp()
{
	m_Params.currentY = std::max(m_Params.currentY - 1, 0);
}
template<typename T>
inline void Selector<T>::MoveDown()
{
	m_Params.currentY = std::min(m_Params.currentY + 1, m_Rows - 1);
}
template<typename T>
inline void Selector<T>::MoveLeft()
{
	m_Params.currentX = std::max(m_Params.currentX - 1, 0);
}
template<typename T>
inline void Selector<T>::MoveRight()
{
	m_Params.currentX = std::min(m_Params.currentX + 1, m_Params.columns - 1);
}

// This function is called when an action is performed. It calls the OnSelection function with the current index and data.
template<typename T>
inline void Selector<T>::OnAction()
{
	int index = GetIndex();

	m_OnSelection(index, m_Data);
}

// This function draws an item at a specific position. If the item is not a wstring, it throws an error.
template<typename T>
inline void Selector<T>::DrawItem(int x, int y, T item)
{
	// Check to see if the type is Wstring
	if constexpr (std::is_same<T, std::wstring>::value) 
	{
		m_Console.Write(x, y, item);

		return;
	}

	// Get the type and let user know to override
	std::string type = typeid(item).name();

	TRPG_ERROR("DATA type [" + type + "] - need to be a wstring. Please create the DrawItem funtion to override.");
}

// This function is called when a selection is made. It writes the index of the selection to the console.
// This function should be overridden in a derived class to provide more specific functionality.
template<typename T>
inline void Selector<T>::OnSelection(int index, std::vector<T> data)
{
	m_Console.Write(50, 20, L"Index: " + std::to_wstring(index));
}

// This function draws all the items in the data vector to the console.
template<typename T>
inline void Selector<T>::Draw()
{
	// If there is no data, nothing to draw.
	if (m_Data.empty()) 
	{
		return;
	}
	
	// Initialize variables for item index, position (x, y), row height, spacing, and maximum data size.
	int itemIndex = 0;
	int x = m_Params.x;
	int y = m_Params.y;
	int rowHeight = m_Params.spacingY;
	int spacingX = m_Params.spacingX;
	int maxData = m_Data.size();

	// Loop through each row.
	for (int i = 0; i < m_Rows; i++)
	{
		// Loop through each column.
		for (int j = 0; j < m_Params.columns; j++) 
		{
			// If the current position matches the cursor position.
			if (i == m_Params.currentY && j == m_Params.currentX) 
			{
				// If the cursor is visible.
				if (m_bShowCursor)
				{
					// Reset the areas behind the cursor as it moves.
					if (m_Params.currentY != 0)
					{
						m_Console.Write(x - (x == 0 ? 0 : 2), y - rowHeight, L" ");
					}
					if (m_Params.currentX != 0)
					{
						m_Console.Write(x - (x == 0 ? 0 : 2) - spacingX, y, L" ");
					}
					if (m_Params.currentY != m_Rows - 1)
					{
						m_Console.Write(x - (x == 0 ? 0 : 2), y + rowHeight, L" ");
					}
					if (m_Params.currentX != m_Params.columns - 1)
					{
						m_Console.Write(x - (x == 0 ? 0 : 2) + spacingX, y, L" ");
					}

					// Draw the cursor.
					m_Console.Write(x - (x == 0 ? 0 : 2), y, m_Params.cursor, RED);
				}
				else
				{
					// Clear the cursor.
					m_Console.Write(x - (x == 0 ? 0 : 2), y, L"  ");
				}
			}

			// If there are still items to draw.
			if (itemIndex < maxData) 
			{
				// Draw the item.
				T item = m_Data[itemIndex];

				m_OnDrawItems(x, y, item);

				// Move to the next position.
				x += spacingX;
				itemIndex++;
			}
		}

		// Move to the next row and reset the x position.
		y += rowHeight;
		x = m_Params.x;
	}
}
