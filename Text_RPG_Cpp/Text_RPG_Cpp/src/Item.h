#pragma once

#include <string>

// Forward declaration of the Player class.
class Player;

// The Item class represents an item in a game.
class Item
{
public: 
	// ItemType is an enum that represents the type of the Item.
	enum ItemType 
	{
		HEALTH = 0,
		STATUS_AFFECT,
		REVIVE,
		BATTLE,
		KEY_ITEM,
		NO_TYPE
	};

private:
	const int MAX_COUNT = 99;

	ItemType m_eItemType; // m_eItemType is an ItemType that represents the type of the Item.

protected:
	// m_Count is the item count (default 1), m_BuyPrice is the item's buy price (default 0), m_SellPrice is the item's sell price (default 0), and m_ItemValue is the item's value (default 0).
	int m_Count{ 1 }, m_BuyPrice{ 0 }, m_SellPrice{ 0 }, m_ItemValue{ 0 };

	// m_sItemName is a wstring that represents the name of the Item.
	std::wstring m_sItemName{ L"Item_Name" };

	// m_sDescription is a wstring that represents the description of the Item.
	std::wstring m_sDescription{ L"Item_Description" };

	// SetType is a function that sets the type of the Item.
	void SetType(ItemType type)
	{
		m_eItemType = type;
	}

public:
	// This is the destructor for the Item class. It's declared as default, which means the compiler will generate it for us.
	virtual ~Item() {}

	// OnUse is a pure virtual function that defines what happens when the Item is used. It must be overridden in any derived class.
	virtual bool OnUse(Player& player) = 0;

	// GtCount returns the count of the Item.
	inline const int GetCount() const
	{
		return m_Count;
	}

	// Decrement decreases the count of the Item by 1. If the count is less than or equal to 0, it sets the count to 0.
	inline bool Decrement(int num = 1)
	{
		if (m_Count <= 0)
		{
			return false;
		}
		if (m_Count - num < 0)
		{
			return false;
		}

		m_Count--;

		if (m_Count < 0)
		{
			m_Count = 0;
		}

		return true;
	}

	// AddItem increases the count of the Item by a specified number.
	bool AddItem(int num = 1)
	{
		if (m_Count + num > MAX_COUNT)
		{
			return false;
		}

		m_Count += num;

		return true;
	}

	// GetItemName returns the name of the Item.
	inline const std::wstring& GetItemName() const 
	{ 
		return m_sItemName; 
	}

	// GetDescription returns the description of the Item.
	inline const std::wstring& GetDescription() const 
	{ 
		return m_sDescription; 
	}

	inline const int GetBuyPrice() const 
	{ 
		return m_BuyPrice; 
	}

	inline const int GetSellPrice() const 
	{ 
		return m_SellPrice; 
	}

	inline const int GetMaxCount() const 
	{ 
		return MAX_COUNT; 
	}

	inline const ItemType GetType() const 
	{ 
		return m_eItemType; 
	}

	inline const int GetItemValue() const 
	{ 
		return m_ItemValue; 
	}
};