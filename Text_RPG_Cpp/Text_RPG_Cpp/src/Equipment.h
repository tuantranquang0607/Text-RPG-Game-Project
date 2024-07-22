#pragma once

#include <string>

// Forward declaration of the Player class.
class Player;

// The StatModifier struct represents a modification to a player's stats.
struct StatModifier
{
	// ModifierType is an enum class that represents the type of the stat modifier.
	enum class ModifierType
	{
		STRENGTH = 0,
		SPEED,
		INTELLIGENCE,
		DEXTERITY,
		ELEMENTAL,
		NO_TYPE
	};

	// ElementalType is an enum class that represents the type of the elemental modifier.
	enum class ElementalType
	{
		FIRE = 0,
		EARTH,
		WIND,
		ICE,
		WATER,
		LIGHTNING,
		NO_TYPE
	};

	// statModifierVal is the value of the stat modifier.
	int statModifierVal;

	// modifierType is the type of the stat modifier.
	ModifierType modifierType;

	// elementalType is the type of the elemental modifier.
	ElementalType elementalType;

	// modifierTypeStr is the string representation of the modifier type.
	std::wstring modifierTypeStr;

	// This is the constructor for the StatModifier struct. It initializes the struct with a value, modifier type, and elemental type.
	StatModifier(int val = 0, ModifierType mod_type = ModifierType::NO_TYPE, ElementalType elemental_type = ElementalType::NO_TYPE) : 
		statModifierVal(val), 
		modifierType(mod_type), 
		elementalType(elemental_type) 
	{
		// Switch case to set the string representation of the modifier type
		switch (mod_type) 
		{
		case StatModifier::ModifierType::STRENGTH:
			modifierTypeStr = L"Strength";
			break;
		case StatModifier::ModifierType::SPEED:
			modifierTypeStr = L"Speed";
			break;
		case StatModifier::ModifierType::INTELLIGENCE:
			modifierTypeStr = L"Intelligence";
			break;
		case StatModifier::ModifierType::DEXTERITY:
			modifierTypeStr = L"Dexterity";
			break;
		case StatModifier::ModifierType::ELEMENTAL:
			modifierTypeStr = L"Elemental";
			break;
		case StatModifier::ModifierType::NO_TYPE:
			modifierTypeStr = L"No Type";
			break;
		default:
			break;
		}
	}
};

// Structures to represent the properties of a weapon and armor
struct WeaponProperties
{
	enum class WeaponType
	{
		SWORD = 0,
		DAGGER,
		BOW,
		STAFF,
		NOT_A_WEAPON
	};

	// Attack power of the weapon
	int attackPwr;

	// Type of the weapon
	WeaponType weaponType;

	// Constructor to initialize the weapon properties
	WeaponProperties(int attack_pwr = 0, WeaponType weapon_type = WeaponType::NOT_A_WEAPON) :
		attackPwr( attack_pwr ),
		weaponType( weapon_type )
	{
	}
};

// Structures to represent the properties of armor
struct ArmorProperties
{
	enum class ArmorType
	{
		HEADGEAR = 0,
		CHEST_BODY,
		FOOTWEAR,
		NOT_ARMOR
	};

	// Defense power of the armor
	int defensePwr;

	// Type of the armor
	ArmorType armorType;

	// Constructor to initialize the armor properties
	ArmorProperties(int defense_pwr = 0, ArmorType armor_type = ArmorType::NOT_ARMOR) :
		defensePwr( defense_pwr ),
		armorType( armor_type )
	{
	}
};

// Class to represent a piece of equipment that a player can use
class Equipment
{
public: 
	enum class EquipType
	{
		WEAPON = 0,
		ARMOR,
		ACCESSORY,
		NO_TYPE
	};

private:
	const int MAX_COUNT = 50;

	// Type of the equipment
	Equipment::EquipType m_eEquipType{ EquipType::NO_TYPE };

protected:
	// Name and description of the equipment
	std::wstring m_sName{ L"" }, m_sDescription{ L"" };

	// Buy price, sell price, count, and weight of the equipment
	int m_BuyPrice{ 0 }, m_SellPrice{ 0 }, m_Count{ 0 }, m_Weight{ 0 };

	// Whether the equipment is equipped
	bool m_bEquipped{ false };

	// Weapon properties of the equipment
	WeaponProperties m_WeaponProperties;

	// Armor properties of the equipment
	ArmorProperties m_ArmorProperties;

	// Stat modifier of the equipment
	StatModifier m_StatModifier;

	// Method to set the type of the equipment
	void SetEquipType(EquipType type) 
	{ 
		m_eEquipType = type; 
	}

public:
	// Destructor of the Equipment class
	virtual ~Equipment() {}

	// Pure virtual methods to be implemented by derived classes
	virtual const int GetValue() const = 0;

	virtual bool OnEquip(Player& player) = 0;

	virtual bool OnRemove(Player& player) = 0;

	// Methods to equip and remove the equipment
	inline void Remove()
	{
		if (m_bEquipped)
		{
			m_bEquipped = false;
		}
	}

	inline void Equip()
	{
		if (!m_bEquipped)
		{
			m_bEquipped = true;
		}
	}

	// Getters for the properties of the equipment
	inline const bool IsEquipped() const
	{
		return m_bEquipped;
	}

	inline const std::wstring& GetName() const
	{
		return m_sName;
	}

	inline const std::wstring& GetDescription() const
	{
		return m_sDescription;
	}

	inline bool Add(int num)
	{
		/*m_Count += num;*/

		if (m_Count + num > MAX_COUNT)
		{
			return false;
		}

		m_Count += num;

		return true;
	}

	inline const int GetCount() const
	{
		return m_Count;
	}

	inline const Equipment::EquipType GetType() const
	{
		return m_eEquipType;
	}

	inline const WeaponProperties& GetWeaponProperties() const
	{
		return m_WeaponProperties;
	}

	inline const ArmorProperties& GetArmorProperties() const
	{
		return m_ArmorProperties;
	}

	inline const StatModifier& GetStatModifier() const
	{
		return m_StatModifier;
	}
};

// Class to represent a weapon that a player can use
class Weapon : public Equipment
{
public:
	// Default constructor and constructor with parameters
	Weapon();

	Weapon(const std::wstring& name, const std::wstring& description, int buy_price, int sell_price, WeaponProperties weapon_properties = WeaponProperties(), StatModifier stat_modifier = StatModifier());

	// Default destructor
	~Weapon() = default;

	// Method to get the value of the weapon, which is its attack power
	inline const int GetValue() const override
	{
		return m_WeaponProperties.attackPwr;
	}

	// Methods to equip and remove the weapon, to be implemented in the .cpp file
	bool OnEquip(Player& player) override;

	bool OnRemove(Player& player) override;
};

// Class to represent an armor that a player can use
class Armor : public Equipment
{
public:
	// Default constructor and constructor with parameters
	Armor();

	Armor(const std::wstring& name, const std::wstring& description, int buy_price, int sell_price, ArmorProperties armor_properties = ArmorProperties(), StatModifier stat_modifier = StatModifier());

	// Default destructor
	~Armor() = default;

	// Method to get the value of the armor, which is its defense power
	inline const int GetValue() const override
	{
		return m_ArmorProperties.defensePwr;
	}

	// Methods to equip and remove the armor, to be implemented in the .cpp file
	bool OnEquip(Player& player) override;

	bool OnRemove(Player& player) override;
};