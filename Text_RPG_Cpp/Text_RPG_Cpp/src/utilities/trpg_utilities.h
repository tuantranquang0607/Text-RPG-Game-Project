#pragma once

#include <vector>
#include <string>
#include <Windows.h>

#include "../Item.h"
#include "../Equipment.h"
#include "ShopParameters.h"

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

// Function declaration to convert a string to an ItemType enum.
Item::ItemType ItemTypeFromString(const std::string& item_type);

// Function declaration to convert a string to an EquipType enum.
Equipment::EquipType EquipTypeFromString(const std::string& equip_type);

// Function declaration to convert a string to a ShopType enum.
ShopParameters::ShopType ShopTypeFromString(const std::string& shopType);

// Function declaration to convert a string to a WeaponType enum.
WeaponProperties::WeaponType WeaponTypeFromString(const std::string& weapon_type);

// Function declaration to convert a string to an ArmorType enum.
ArmorProperties::ArmorType ArmorTypeFromString(const std::string& armor_type);

// Function declaration to convert a string to a ModifierType enum.
StatModifier::ModifierType ModifierTypeFromString(const std::string& mod_type);

// Function declaration to convert a string to an ElementalType enum.
StatModifier::ElementalType ElementalTypeFromString(const std::string& elemental_type);