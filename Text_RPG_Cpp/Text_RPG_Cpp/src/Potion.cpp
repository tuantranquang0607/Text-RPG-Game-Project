#include "Potion.h"
#include "Player.h"

Potion::Potion(const std::wstring& item_name, const std::wstring& desc, int health, int buy_price)
{
	m_sItemName = item_name; // Set the name of the potion
	m_sDescription = desc; // Set the description of the potion
	m_ItemValue = health; // Set the health value of the potion
	m_BuyPrice = buy_price; // Set the buy price of the potion
	m_SellPrice = buy_price / 2; // Set the sell price of the potion as half of the buy price

	SetType(ItemType::HEALTH); // Set the type of the item as HEALTH
}

// Destructor for the Potion class
Potion::~Potion() 
{

}

// Method to use the potion
bool Potion::OnUse(Player& player)
{
	if (m_Count <= 0) // If there are no potions left, return false
	{
		return false;
	}

	const auto& hp = player.GetHP(); // Get the current health points of the player
	const auto& hp_max = player.GetMaxHP(); // Get the maximum health points of the player

	if (hp >= hp_max) // If the player's health is already at maximum, return false
	{
		return false;
	}

	player.HealHP(m_ItemValue); // Heal the player by the value of the potion

	Decrement(); // Decrease the count of the potion

	return true; // Return true indicating the potion was used successfully
}
