#pragma once

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
template <typename Y = std::wstring> class Selector
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
	// Constructor and destructor for the Selector class.
	Selector();
	~Selector();

	// Method to set the data for the selector.
	void SetData(std::vector<T> data) 
	{ 
		mData = data 
	};

	// Method to get the data for the selector.
	const std::vector<T>& GetData() 
	{ 
		return mData; 
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