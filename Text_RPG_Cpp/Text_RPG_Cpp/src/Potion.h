#pragma once

#include "Item.h"

class Player;

// Potion class, derived from the Item class
class Potion : public Item
{
public:
	// Default constructor that initializes a Potion with a default name, description, health value, and buy price
	Potion() : Potion(L"Item_name", L"Item Description", 10, 10) {}

	// Overloaded constructor that initializes a Potion with given name, description, health value, and buy price. If health and buy price are not provided, they are set to 10 and 0 respectively.
	Potion(const std::wstring& item_name, const std::wstring& desc, int health = 10, int buy_price = 0);
	
	// Destructor for the Potion class
	~Potion();

	// Method to use the potion. This method is overridden from the Item class.
	bool OnUse(Player& player) override;
};
