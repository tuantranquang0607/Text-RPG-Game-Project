#pragma once

#define NOMINMAX

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
	Console & m_Console;
	Keyboard & m_Keyboard;

	std::function<void(int, std::vector<T>)> m_OnSelection;
	std::function<void(int, int, T)> m_OnDrawItems;
	std::vector<T> m_Data;

	SelectorParams m_Params;

	bool m_bShowCursor;

	int m_Rows;

public:
	// Constructors and destructor for the Selector class.
	Selector(Console & console, Keyboard & keyboard, std::vector<T> data, SelectorParams params = SelectorParams());
	Selector(Console & console, 
			 Keyboard & keyboard, 
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
	const std::vector<T>& GetData() 
	{ 
		return m_Data; 
	};

	// Method to set the selection function for the selector.
	void SelectionFunc(std::function<void(int, std::vector<T>)> on_selection) 
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

	// Methods to process inputs, move the selection, handle actions, draw items, handle selections, and draw the selector.
	void ProcessInputs();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	void OnAction();
	void DrawItem(int x, int y, T item);
	void OnSelection(int index, std::vector<T> data);
	void Draw();
};

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

template<typename T>
inline Selector<T>::Selector(Console & console,
							 Keyboard & keyboard, 
							 std::function<void(int, std::vector<T>)> on_selection, 
							 std::function<void(int, int, T)> on_draw_item, 
							 std::vector<T> data, 
							 SelectorParams params )
	: m_Console(Console), 
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

template<typename T>
inline Selector<T>::~Selector()
{

}

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

template<typename T>
inline void Selector<T>::OnAction()
{
	int index = GetIndex();

	m_OnSelection(index, m_Data);
}

template<typename T>
inline void Selector<T>::DrawItem(int x, int y, T item)
{
	// Check to see if the type is Wstring
	if constexpr (std::is_same<T, std::string>::value) 
	{
		m_Console.Write(x, y, item);

		return;
	}

	// Get the type and let user know to override
	std::string type = typeid(item).name();

	TRPG_ERROR("DATA type [" + type + "] - need to be a wstring. Please create the DrawItem funtion to override.");
}

// This function should be overridden.
template<typename T>
inline void Selector<T>::OnSelection(int index, std::vector<T> data)
{
	m_Console.Write(50, 20, L"Index: " + std::to_string(index));
}

template<typename T>
inline void Selector<T>::Draw()
{
	// If there is no data, nothing to draw.
	if (m_Data.empty()) 
	{
		return;
	}

	int itemIndex = 0;
	int x = m_Params.x;
	int y = m_Params.y;
	int rowHeight = m_Params.spacingY;
	int spacingX = m_Params.spacingX;
	int maxData = m_Data.size();

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Params.columns; j++) 
		{
			if (i == m_Params.currentY && j == m_Params.currentX) 
			{
				if (m_bShowCursor)
				{
					// Reset the areas behind the cursor as it moves.
					if (i != 0) 
					{
						m_Console.Write(x - (x == 0 ? 0 : 2), y - rowHeight, L"  ");
					}

					m_Console.Write(x - (x == 0 ? 0 : 2), y + rowHeight, L"  ");
					m_Console.Write(x - (x == 0 ? 0 : 2) - spacingX, L"  ");
					m_Console.Write(x - (x == 0 ? 0 : 2) + spacingX, L"  ");

					// Draw the cursor.
					m_Console.Write(x - (x == 0 ? 0 : 2), y, m_Params.cursor, RED);
				}
				else
				{
					// Clear the cursor.
					m_Console.Write(x - (x == 0 ? 0 : 2), y, L"  ");
				}
			}

			if (itemIndex < maxData) 
			{
				// Draw the item.
				T item = m_Data[itemIndex];

				m_OnDrawItems(x, y, item);

				x += spacingX;
				itemIndex++;
			}
		}

		y += rowHeight;
		x = m_Params.x;
	}
}
