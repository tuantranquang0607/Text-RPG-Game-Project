#pragma once

#include <string>
#include <vector>

class Actor
{
public:
	// ActorType is an enum class that represents the type of the Actor.
	enum class ActorType
	{
		WARRIOR = 0, BLACK_MAGE, THIEF,
	};

private:
	// m_EquipmentSlotLabels is a vector of wstrings that represents the labels for the equipment slots.
	const std::vector<std::wstring> m_EquipmentSlotLabels{ L"Weapon: ", L"Headgear :", L"Armor: ", L"Footwear: ", L"Accessory: "};
	/*std::vector<std::wstring> m_EquipmentSlotLabels;*/

protected:
	// m_sName is a wstring that represents the name of the Actor.
	std::wstring m_sName;

	// m_Level, m_XP, m_XPToNextLevel, m_HP, m_MaxHP are integers that represent the level, experience points, experience points to the next level, health points, and maximum health points of the Actor, respectively.
	int m_Level, m_XP, m_XPToNextLevel, m_HP, m_MaxHP;

	// m_bDead is a boolean that represents whether the Actor is dead.
	bool m_bDead;

	// m_eActorType is an ActorType that represents the type of the Actor.
	ActorType m_eActorType;

public:
	// This is the default constructor for the Actor class.
	Actor();

	// This is a constructor for the Actor class that initializes the class with a name, level, maximum health points, and type.
	Actor( const std::wstring & name, int level, int max_hp, ActorType type = ActorType::WARRIOR );

	// This is the destructor for the Actor class.
	~Actor() = default;

	// These are getter methods for the Actor class. They return the health points, maximum health points, equipment slot labels, death status, name, level, experience points, and experience points to the next level of the Actor.
	inline const int GetHP() const
	{
		return m_HP;
	}

	inline const int GetMaxHP() const 
	{ 
		return m_MaxHP; 
	}

	inline const std::vector<std::wstring> GetEquipmentSlotLabels() const 
	{ 
		return m_EquipmentSlotLabels; 
	}

	inline const bool IsDead() const 
	{ 
		return m_bDead; 
	}

	inline const std::wstring & GetName() const 
	{ 
		return m_sName; 
	}

	const int GetLevel() const 
	{ 
		return m_Level; 
	}

	const int GetXP() const 
	{ 
		return m_XP; 
	}

	const int GetXPToNextLevel() const 
	{ 
		return m_XPToNextLevel; 
	}

	// These are methods that modify the health points of the Actor.
	void HealHP( int hp );

	void TakeDamage( int hp );
};