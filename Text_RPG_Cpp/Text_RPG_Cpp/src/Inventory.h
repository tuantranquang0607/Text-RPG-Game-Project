#pragma once

#include "Item.h"
#include "Equipment.h"

#include <vector>
#include <memory>

// Forward declaration of the Player class.
class Player;

// The Inventory class represents a collection of items and equipment.
class Inventory
{
private:
	// m_Items is a vector of shared pointers to Item objects. It represents the items in the inventory.
	std::vector<std::shared_ptr<Item>> m_Items;

	// m_Equipment is a vector of shared pointers to Equipment objects. It represents the equipment in the inventory.
	std::vector<std::shared_ptr<Equipment>> m_Equipment;

public:
	// This is the default constructor for the Inventory class.
	Inventory();

	// This is the destructor for the Inventory class. It's declared as default, which means the compiler will generate it for us.
	~Inventory() = default;

	// GetItems returns a const reference to the vector of items in the inventory.
	const std::vector<std::shared_ptr<Item>>& GetItems()
	{
		return m_Items;
	}

	// GetEquipment returns a const reference to the vector of equipment in the inventory.
	const std::vector<std::shared_ptr<Equipment>>& GetEquipment()
	{
		return m_Equipment;
	}

	// AddItem adds a new item to the inventory.
	bool AddItem(std::shared_ptr<Item> newItem);

	// AddEquipment adds new equipment to the inventory.
	bool AddEquipment(std::shared_ptr<Equipment> newEquipment);

	// UseItem uses an item from the inventory, given the player and the index of the item.
	bool UseItem(Player& player, int index);
};
