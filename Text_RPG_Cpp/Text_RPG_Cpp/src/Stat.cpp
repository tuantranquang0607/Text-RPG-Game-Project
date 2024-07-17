#include "Stat.h"
#include "Logger.h"

#include <iostream>

// Default constructor for Stats class, initializes all stats to 0
Stats::Stats() : Stats(0, 0, 0, 0, 0)
{
}

// Constructor for Stats class, initializes stats with given values
Stats::Stats(int strength, int intelligence, int speed, int dexterity, int stamina) : m_StatList
	{
		{L"Attack", 0},
		{L"Defense", 0},
		{L"Magic", 0},
		{L"Strength", strength},
		{L"Speed", speed},
		{L"Intelligence", intelligence},
		{L"Dexterity", dexterity},
		{L"Stamina", stamina},
	},
	m_StatModifierList
	{
		{L"Strength", 0},
		{L"Speed", 0},
		{L"Intelligence", 0},
		{L"Dexterity", 0},
		{L"Stamina", 0},
	},
	m_EquipSlotList
	{
		{EquipSlots::WEAPON, 0},
		{EquipSlots::HEADGEAR, 0},
		{EquipSlots::CHEST_BODY, 0},
		{EquipSlots::FOOTWEAR, 0},
		{EquipSlots::ACCESSORY, 0},
	}
{
	// Initialize the Attack and Defense
	UpdateStats();
}

// Method to get a stat value by key
const int Stats::GetStat(const std::wstring& key)
{
	if (m_StatList.find(key) == m_StatList.end()) 
	{
		// TRPG_ERROR("[" + key + "] -- Is not a valid stat!");

		std::wcout << L"[" + key + L"] -- Is not a valid stat!\n";

		return 0;
	}

	return m_StatList[key];

	/*return 0;*/
}

// Method to get a stat modifier value by key
const int Stats::GetModifier(const std::wstring& key)
{
	if (m_StatModifierList.find(key) == m_StatModifierList.end()) 
	{
		// TRPG_ERROR("[" + key + "] -- Is not a valid stat!");
		
		std::wcout << L"[" + key + L"] -- Is not a valid stat modifier!\n";

		return 0;
	}

	return m_StatModifierList[key];

	/*return 0;*/
}

// Method to get an equipment value by slot
const int Stats::GetEquipmentValue(EquipSlots slot)
{
	if (m_EquipSlotList.find(slot) == m_EquipSlotList.end()) 
	{
		// TRPG_ERROR("[" + key + "] -- Is not a valid stat!");

		std::wcout << L"--Invalid slot!\n";

		return 0;
	}

	return m_EquipSlotList[slot];

	/*return 0;*/
}

// Method to set a stat modifier value by key
void Stats::SetModifier(const std::wstring& key, int value)
{
	if (m_StatModifierList.find(key) == m_StatModifierList.end()) 
	{
		// TRPG_ERROR("[" + key + "] -- Is not a valid stat!");

		std::wcout << L"[" + key + L"] -- Is not a valid stat modifier!\n";

		return;
	}

	m_StatModifierList[key] = value;
}

// Method to set an equipment value by slot
void Stats::SetEquipmentValue(EquipSlots slot, int value)
{
	if (m_EquipSlotList.find(slot) == m_EquipSlotList.end()) 
	{
		// TRPG_ERROR("[" + key + "] -- Is not a valid stat!");

		std::wcout << L"--Invalid slot!\n";


		return;
	}

	m_EquipSlotList[slot] = value;
}

// Method to set a stat value by key
void Stats::SetStat(const std::wstring& key, int value)
{
	if (m_StatList.find(key) == m_StatList.end()) 
	{
		// TRPG_ERROR("[" + key + "] -- Is not a valid stat!");

		std::wcout << L"[" + key + L"] -- Is not a valid stat!\n";

		return;
	}

	m_StatList[key] = value;
}

// Method to update the Attack and Defense stats based on other stats and equipment
void Stats::UpdateStats()
{
	// Update attack power stat
	m_StatList[L"Attack"] = m_EquipSlotList[EquipSlots::WEAPON] +
		(m_StatList[L"Strength"] + m_StatModifierList[L"Strength"]) +
		((m_StatList[L"Intelligence"] + m_StatModifierList[L"Intelligence"]) / 5) +
		((m_StatList[L"Dexterity"] + m_StatModifierList[L"Dexterity"]) / 5);

	// Update defense power stat
	m_StatList[L"Defense"] = m_EquipSlotList[EquipSlots::HEADGEAR] + m_EquipSlotList[EquipSlots::CHEST_BODY] +
		m_EquipSlotList[EquipSlots::FOOTWEAR] +
		((m_StatList[L"Strength"] + m_StatModifierList[L"Strength"]) / 5) +
		((m_StatList[L"Intelligence"] + m_StatModifierList[L"Intelligence"]) / 5) +
		((m_StatList[L"Speed"] + m_StatModifierList[L"Speed"]) / 5) +
		((m_StatList[L"Dexterity"] + m_StatModifierList[L"Dexterity"]) / 5);
}
