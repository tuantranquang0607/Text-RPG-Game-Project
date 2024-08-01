#pragma once

#include <memory>
#include <string>
#include <concepts>

#include "../Item.h"
#include "../Equipment.h"
#include "../Potion.h"

class ItemCreator
{
private:
	// This private template function creates a shared pointer to an object of type T. The object is constructed with the provided arguments. The function requires that T is constructible from Args.
	template <typename T, typename ...Args> requires std::constructible_from<T, Args...> static std::shared_ptr<T> Create(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// This is a fallback template function that returns a null shared pointer. It is used when the type T is not constructible from Args.
	template <typename T, typename ...Args> static std::shared_ptr<T> Create(Args&&... args)
	{
		return nullptr;
	}

public:
	// This public function creates an item of a specific type. The type is determined by the ItemType enum. Currently, only health potions can be created. Other types return a null shared pointer.
	template <class ...Args> static std::shared_ptr<Item> CreateItem(Item::ItemType type, Args&& ...args)
	{
		switch (type)
		{
			case Item::ItemType::HEALTH:
				return Create<Potion>(std::forward<Args>(args) ...);
			case Item::ItemType::REVIVE:
				return nullptr;
			case Item::ItemType::STATUS_AFFECT:
				return nullptr;
			case Item::ItemType::BATTLE:
				return nullptr;
			case Item::ItemType::KEY_ITEM:
				return nullptr;
			case Item::ItemType::NO_TYPE:
				return nullptr;
			default:
				return nullptr;
		}
	}

	// This public function creates a piece of equipment of a specific type. The type is determined by the EquipType enum. Currently, only weapons and armor can be created. Other types return a null shared pointer.
	template <class ...Args> static std::shared_ptr<Equipment> CreateEquipment(Equipment::EquipType type, WeaponProperties weapon_props, ArmorProperties armor_props, StatModifier stat_mod, Args&& ...args)
	{
		switch (type)
		{
			case Equipment::EquipType::WEAPON:
				return Create<Weapon>(std::forward<Args>(args)..., weapon_props, stat_mod);
			case Equipment::EquipType::ARMOR:
				return Create<Armor>(std::forward<Args>(args)..., armor_props, stat_mod);
			case Equipment::EquipType::ACCESSORY:
				return nullptr;
			case Equipment::EquipType::NO_TYPE:
				return nullptr;
			default:
				return nullptr;
		}
	}
};