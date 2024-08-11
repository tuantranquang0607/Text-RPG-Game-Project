#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Stat.h"
#include "Equipment.h"

class Actor
{
public:
	// ActorType is an enum class that represents the type of the Actor.
	enum class ActorType { WARRIOR = 0, BLACK_MAGE, THIEF, FIGHTER };

private:
	// m_EquipmentSlotLabels is a vector of wstrings that represents the labels for the equipment slots.
	const std::vector<std::wstring> m_EquipmentSlotLabels{ L"Weapon", L"Headgear", L"Armor", L"Footwear", L"Accessory" };

	/*std::vector<std::wstring> m_EquipmentSlotLabels;*/

	const std::vector<std::wstring> m_StatLabels{ L"Attack", L"Strength", L"Intelligence", L"Speed", L"Dexterity", L"Stamina" };

protected:
	// m_sName is a wstring that represents the name of the Actor and ID.
	std::wstring m_sName, m_sID;

	// m_Level, m_XP, m_XPToNextLevel, m_HP, m_MaxHP are integers that represent the level, experience points, experience points to the next level, health points, and maximum health points of the Actor, respectively.
	int m_Level, m_XP, m_XPToNextLevel, m_HP, m_MaxHP;

	// m_MP, m_MaxMP are integers that represent the magic points and maximum magic points of the Actor, respectively.
	int m_MP, m_MaxMP;

	// m_bDead is a boolean that represents whether the Actor is dead.
	bool m_bDead;

	// m_eActorType is an ActorType that represents the type of the Actor. Variable to store the type of the actor
	ActorType m_eActorType;

	// Unordered maps to store the actor's equipment and equipment slots
	std::unordered_map<Equipment::EquipType, std::shared_ptr<Equipment>> m_mapEquipment;
	std::unordered_map<Stats::EquipSlots, std::shared_ptr<Equipment>> m_mapEquipmentSlots;

	// Variable to store the actor's stats
	Stats m_Stats;

public:
	// This is the default constructor for the Actor class.
	Actor();

	// This is a constructor for the Actor class that initializes the class with a name, level, maximum health points, and type.
	Actor( const std::wstring& name, const std::wstring& id, int level, int max_hp, ActorType type = ActorType::WARRIOR );

	// This is the destructor for the Actor class.
	~Actor() = default;

	// Getter methods for the actor's health points, maximum health points, equipment slot labels, death status, name, level, experience points, and experience points to the next level
	inline const int GetHP() const { return m_HP; }

	inline const int GetMaxHP() const { return m_MaxHP; }

	inline const std::vector<std::wstring> GetEquipmentSlotLabels() const { return m_EquipmentSlotLabels; }
	inline const std::vector<std::wstring> GetStatLabels() const { return m_StatLabels; }

	std::unordered_map<Equipment::EquipType, std::shared_ptr<Equipment>>& GetEquippedItems() { return m_mapEquipment; }
	std::unordered_map<Stats::EquipSlots, std::shared_ptr<Equipment>>& GetEquippedItemsSlots(){ return m_mapEquipmentSlots; }

	Stats& GetStats() { return m_Stats; }

	inline const bool IsDead() const { return m_bDead; }

	inline const std::wstring& GetName() const { return m_sName; }

	inline const std::wstring& GetID() const { return m_sID; }

	const int GetLevel() const { return m_Level; }

	const int GetXP() const { return m_XP; }

	const int GetMP() const { return m_MP; }

	const int GetMaxMP() const { return m_MaxMP; }

	const int GetXPToNextLevel() const { return m_XPToNextLevel; }

	// These are methods that modify the health points of the Actor.
	void HealHP( int hp );

	// This method is used to increase the actor's health points by a certain amount.
	void TakeDamage( int hp );

	bool UseMP(int mp);
};