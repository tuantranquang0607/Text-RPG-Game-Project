#pragma once

#include <unordered_map>
#include <string>

// Class to represent the statistics of a player in a game
class Stats
{
public: enum class EquipSlots // Enum class to represent the equipment slots
{
	WEAPON = 0,
	HEADGEAR,
	CHEST_BODY,
	FOOTWEAR,
	ACCESSORY,
	NO_SLOT
};
private:
	// Unordered maps to store the player's stats, stat modifiers, and equipment values
	std::unordered_map<std::wstring, int> m_StatList;

	std::unordered_map<std::wstring, int> m_StatModifierList;

	std::unordered_map<EquipSlots, int> m_EquipSlotList;

public:
	// Default constructor and constructor with parameters for Stats class
	Stats();

	Stats(int strength, int intelligence, int speed, int dexterity, int stamina);

	// Default destructor for Stats class
	~Stats() = default;

	// Getters for the stat list, modifier list, and equipment slot list
	inline const std::unordered_map<std::wstring, int>& GetStatList() const 
	{ 
		return m_StatList; 
	}

	inline const std::unordered_map<std::wstring, int>& GetModifierList() const 
	{ 
		return m_StatModifierList; 
	}

	inline const std::unordered_map<EquipSlots, int>& GetEquipSlotList() const 
	{ 
		return m_EquipSlotList; 
	}

	// Methods to get a stat, modifier, or equipment value by key or slot
	const int GetStat(const std::wstring& key);

	const int GetModifier(const std::wstring& key);

	const int GetEquipmentValue(EquipSlots slot);

	// Methods to set a stat, modifier, or equipment value by key or slot
	void SetModifier(const std::wstring& key, int value);

	void SetEquipmentValue(EquipSlots slot, int value);

	void SetStat(const std::wstring& key, int value);

	// Method to update the stats based on the modifiers and equipment
	void UpdateStats();
};