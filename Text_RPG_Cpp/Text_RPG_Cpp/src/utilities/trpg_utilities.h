#pragma once

#include <vector>
#include <string>
#include <Windows.h>

#include "../Item.h"

// Template function to remove an element from a vector at a given index
template <typename T> 
void remove(std::vector<T>& vec, size_t index)
{
	vec.erase(vec.begin() + index);
}

// Function declarations
std::wstring CharToWide(const char* str);
std::string WideToStr(const std::wstring& wstr);
std::wstring PadNumbers(int num);


Item::ItemType ItemTypeFromString(const std::string& item_type);