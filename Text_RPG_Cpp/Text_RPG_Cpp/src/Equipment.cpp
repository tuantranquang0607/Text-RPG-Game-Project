#include "Equipment.h"
#include "Player.h"

// Default constructor for Weapon class
Weapon::Weapon() : Weapon(L"Weapon_Name", L"Weapon Description", 0, 0)
{
}

// Constructor for Weapon class with parameters
Weapon::Weapon(const std::wstring& name, const std::wstring& description, int buy_price, int sell_price, WeaponProperties weapon_properties, StatModifier stat_modifier)
{
	m_sName = name; // Set the name of the weapon
	m_sDescription = description; // Set the description of the weapon
	m_BuyPrice = buy_price; // Set the buy price of the weapon
	m_SellPrice = sell_price; // Set the sell price of the weapon
	m_StatModifier = stat_modifier; // Set the stat modifier of the weapon
	SetEquipType(EquipType::WEAPON); // Set the equipment type to WEAPON
	m_WeaponProperties = weapon_properties; // Set the weapon properties
	m_ArmorProperties = ArmorProperties(); // Initialize the armor properties
}

// Method to equip the weapon
bool Weapon::OnEquip(Player& player)
{
	/*return false;*/

	// Get the value of the weapon
	const auto& item_pwr = GetValue();

	// Get the player's stats
	auto& player_stats = player.GetStats();

	// Set the weapon power
	player_stats.SetEquipmentValue(Stats::EquipSlots::WEAPON, item_pwr);

	// Get the stat modifier
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
	{
		player_stats.SetModifier(stat_modifier.modifierTypeStr, stat_modifier.statModifierVal); // Set the stat modifier
	}

	// Equip the weapon
	Equip();

	// Update the player's stats
	player_stats.UpdateStats();

	return true;
}

// Method to remove the weapon
bool Weapon::OnRemove(Player& player)
{
	/*return false;*/

	// Get the player's stats
	auto& player_stats = player.GetStats();

	// Remove the weapon power
	player_stats.SetEquipmentValue(Stats::EquipSlots::WEAPON, 0);

	// Get the stat modifier
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
	{
		player_stats.SetModifier(stat_modifier.modifierTypeStr, 0); // Remove the stat modifier
	}

	// Remove the weapon
	Remove();

	// Update the player's stats
	player_stats.UpdateStats();

	return true;
}

// Default constructor for Armor class
Armor::Armor() : Armor(L"Armor_Name", L"Armor Description", 0, 0)
{
}

// Constructor for Armor class with parameters
Armor::Armor(const std::wstring& name, const std::wstring& description, int buy_price, int sell_price, ArmorProperties armor_properties, StatModifier stat_modifier)
{
	m_sName = name; // Set the name of the armor
	m_sDescription = description; // Set the description of the armor
	m_BuyPrice = buy_price; // Set the buy price of the armor
	m_SellPrice = buy_price / 2; // Set the sell price of the armor
	m_StatModifier = stat_modifier; // Set the stat modifier of the armor
	SetEquipType(EquipType::ARMOR); // Set the equipment type to ARMOR
	m_WeaponProperties = WeaponProperties(); // Initialize the weapon properties
	m_ArmorProperties = armor_properties; // Set the armor properties
}

// Method to equip the armor
bool Armor::OnEquip(Player& player)
{
	/*return false;*/

	// Get the value of the armor
	const auto& item_pwr = GetValue();

	// Get the player's stats
	auto& player_stats = player.GetStats();

	// Initialize the equipment slot
	Stats::EquipSlots slot = Stats::EquipSlots::NO_SLOT;

	// Determine the equipment slot based on the armor type
	switch (m_ArmorProperties.armorType) 
	{
	case ArmorProperties::ArmorType::HEADGEAR:
		slot = Stats::EquipSlots::HEADGEAR; 
		break;
	case ArmorProperties::ArmorType::CHEST_BODY: 
		slot = Stats::EquipSlots::CHEST_BODY; 
		break;
	case ArmorProperties::ArmorType::FOOTWEAR: 
		slot = Stats::EquipSlots::FOOTWEAR; 
		break;
	case ArmorProperties::ArmorType::NOT_ARMOR: 
		slot = Stats::EquipSlots::NO_SLOT; 
		return false;
	default: 
		slot = Stats::EquipSlots::NO_SLOT; 
		return false;
	}

	// Get the stat modifier
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
	{
		player_stats.SetModifier(stat_modifier.modifierTypeStr, stat_modifier.statModifierVal); // Set the stat modifier
	}

	// Set the armor power
	player_stats.SetEquipmentValue(slot, item_pwr);

	// Equip the armor
	Equip();

	// Update the player's stats
	player_stats.UpdateStats();

	return true;
}

// Method to remove the armor
bool Armor::OnRemove(Player& player)
{
	/*return false;*/

	// Get the player's stats
	auto& player_stats = player.GetStats();

	// Initialize the equipment slot
	Stats::EquipSlots slot = Stats::EquipSlots::NO_SLOT;

	// Determine the equipment slot based on the armor type
	switch (m_ArmorProperties.armorType) 
	{
	case ArmorProperties::ArmorType::HEADGEAR: 
		slot = Stats::EquipSlots::HEADGEAR; 
		break;
	case ArmorProperties::ArmorType::CHEST_BODY: 
		slot = Stats::EquipSlots::CHEST_BODY; 
		break;
	case ArmorProperties::ArmorType::FOOTWEAR: 
		slot = Stats::EquipSlots::FOOTWEAR; 
		break;
	case ArmorProperties::ArmorType::NOT_ARMOR: 
		slot = Stats::EquipSlots::NO_SLOT; 
		return false;
	default: 
		slot = Stats::EquipSlots::NO_SLOT; 
		return false;
	}

	// Get the stat modifier
	const auto& stat_modifier = GetStatModifier();

	if (stat_modifier.modifierType != StatModifier::ModifierType::NO_TYPE)
	{
		player_stats.SetModifier(stat_modifier.modifierTypeStr, 0); // Remove the stat modifier
	}

	// Remove the armor power
	player_stats.SetEquipmentValue(slot, 0);

	// Remove the armor
	Remove();

	// Update the player's stats
	player_stats.UpdateStats();

	return true;
}
