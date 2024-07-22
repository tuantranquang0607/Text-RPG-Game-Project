#include "Inventory.h"
#include "Logger.h"
#include "utilities/trpg_utilities.h"

// Default constructor for Inventory class
Inventory::Inventory()
{
}

// Method to add a new item to the inventory
bool Inventory::AddItem(std::shared_ptr<Item> newItem)
{
	// Loop over each item in the inventory
	for (auto& item : m_Items)
	{
		// If the item already exists in the inventory, increase its count
		if (item->GetItemName() == newItem->GetItemName())
		{
			return item->AddItem(newItem->GetCount());
		}
	}

	// If the item does not exist in the inventory, add it
	m_Items.push_back(std::move(newItem));

	return true;
}

// Method to add new equipment to the inventory
bool Inventory::AddEquipment(std::shared_ptr<Equipment> newEquipment)
{
	// Loop over each equipment in the inventory
	for (auto& equip : m_Equipment) 
	{
		// If the equipment already exists in the inventory, increase its count
		if (equip->GetName() == newEquipment->GetName())
		{
			return equip->Add(newEquipment->GetCount());
		}
	}

	// If the equipment does not exist in the inventory, add it
	m_Equipment.push_back(std::move(newEquipment));

	return true;
}

// Method to use an item from the inventory
bool Inventory::UseItem(Player& player, int index)
{
	// If the inventory is empty, print an error message and return false
	if (m_Items.empty())
	{
		TRPG_ERROR("Failed to use items! Items are empty.");

		return false;
	}

	// If the index is out of range, print an error message and return false
	if (index >= m_Items.size())
	{
		TRPG_ERROR("Failed to use items! Index out of item vector size - INDEX[" + std::to_string(index) + "]");

		return false;
	}

	// Use the item
	m_Items[index]->OnUse(player);

	// If the count of the item is 0 or less, remove it from the inventory
	if (m_Items[index]->GetCount() <= 0)
	{
		remove(m_Items, index);
	}

	return true;
}
