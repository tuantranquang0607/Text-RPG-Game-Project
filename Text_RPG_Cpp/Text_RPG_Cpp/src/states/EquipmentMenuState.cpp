#include "EquipmentMenuState.h"
#include "../Player.h"
#include "../Console.h"
#include "StateMachine.h"
#include "../inputs/Keyboard.h"

#include <cassert>

using namespace std::placeholders;

void EquipmentMenuState::DrawEquipment()
{
}

void EquipmentMenuState::DrawPlayerInfo()
{
}

void EquipmentMenuState::DrawStatPrediction()
{
}

void EquipmentMenuState::DrawStatModifier(int x, int y, const std::wstring& stat, int value)
{
}

void EquipmentMenuState::OnMenuSelect(int index, std::vector<std::wstring> data)
{
}

void EquipmentMenuState::OnEquipSelect(int index, std::vector<std::shared_ptr<Equipment>> data)
{
}

void EquipmentMenuState::OnSlotSelect(int index, std::vector<std::wstring> data)
{
	const auto& slot_name = data[index];

	Equipment::EquipType equipType = Equipment::EquipType::NO_TYPE;

	ArmorProperties::ArmorType armor_type = ArmorProperties::ArmorType::NOT_ARMOR;

	if (slot_name == L"Weapon")
	{
		m_eEquipSlots = Stats::EquipSlots::WEAPON;
		equipType = Equipment::EquipType::WEAPON;
	}
	else if (slot_name == L"Headgear")
	{
		m_eEquipSlots = Stats::EquipSlots::HEADGEAR;
		equipType = Equipment::EquipType::ARMOR;
		armor_type = ArmorProperties::ArmorType::HEADGEAR;
	}
	else if (slot_name == L"Armor")
	{
		m_eEquipSlots = Stats::EquipSlots::CHEST_BODY;
		equipType = Equipment::EquipType::ARMOR;
		armor_type = ArmorProperties::ArmorType::CHEST_BODY;
	}
	else if (slot_name == L"Footwear")
	{
		m_eEquipSlots = Stats::EquipSlots::FOOTWEAR;
		equipType = Equipment::EquipType::ARMOR;
		armor_type = ArmorProperties::ArmorType::FOOTWEAR;
	}
	else if (slot_name == L"Accessory")
	{
		m_eEquipSlots = Stats::EquipSlots::ACCESSORY;
		equipType = Equipment::EquipType::ARMOR;
	}
	else
	{
		assert(false, &"SHOULD BE A VALID EQUIP TYPE");

		return;
	}

	if (m_bRemoveEquipment)
	{
		RemoveEquipment(index, data);
		return;
	}

	std::vector<std::shared_ptr<Equipment>> selectedEquipment{};

	for (const auto& item : m_Player.GetInventory().GetEquipment())
	{
		const auto& type = item->GetType();
		if (type != equipType || item->IsEquipped())
		{
			continue;
		}

		if (type == Equipment::EquipType::ARMOR && item->GetArmorProperties().armorType != armor_type)
		{
			continue;
		}

		selectedEquipment.push_back(item);
	}

	m_EquipmentSelector.SetData(selectedEquipment);
	m_sCurrentSlot = slot_name;
	m_EquipSlotSelector.HideCursor();
	m_EquipmentSelector.ShowCursor();
	m_bInSlotSelect = false;
}

void EquipmentMenuState::RenderEquip(int x, int y, std::shared_ptr<Equipment> item)
{
}

void EquipmentMenuState::RenderEquipSlots(int x, int y, const std::wstring& item)
{
}

void EquipmentMenuState::RemoveEquipment(int index, std::vector<std::wstring>& data)
{
	const auto& item = m_Player.GetEquippedItemsSlots()[m_eEquipSlots];
}

void EquipmentMenuState::UpdateIndex()
{
}

EquipmentMenuState::EquipmentMenuState(Player& player, Console& console, StateMachine& stateMachine, Keyboard& keyboard) :
	m_Console(console),
	m_StateMachine(stateMachine),
	m_Keyboard(keyboard),
	m_Player(player),
	m_MenuSelector{
		console,
		keyboard,
		{L"EQUIP", L"REMOVE", L"OPTIMIZE"},
		SelectorParams{42, 10, 3, 15, 2} },
	m_EquipSlotSelector{
		console,
		keyboard,
		std::bind(&EquipmentMenuState::OnSlotSelect, this, _1, _2),
		std::bind(&EquipmentMenuState::RenderEquipSlots, this, _1, _2, _3),
		player.GetEquipmentSlotLabels(),
		SelectorParams{30, 15, 1, 2, 1} },
	m_EquipmentSelector{
		console,
		keyboard,
		std::bind(&EquipmentMenuState::OnEquipSelect, this, _1, _2),
		std::bind(&EquipmentMenuState::RenderEquip, this, _1, _2, _3),
		player.GetInventory().GetEquipment(),
		SelectorParams{30, 34, 3, 20, 2} },
	m_bExitGame{ false },
	m_bInMenuSelect{ true },
	m_bInSlotSelect{ false },
	m_bRemoveEquipment{ false },
	m_ScreenWidth{ console.GetScreenWidth() },
	m_ScreenHeight{ console.GetScreenHeight() },
	m_CenterScreenW{ console.GetHalfWidth() },
	m_PanelBarX{ m_CenterScreenW - (PANEL_BARS / 2) },
	m_sCurrentSlot{ L"NO_SLOT" },
	m_eEquipSlots{ Stats::EquipSlots::NO_SLOT },
{
	m_MenuSelector.SetSelectionFunc(std::bind(&EquipmentMenuState::OnMenuSelect, this, _1, _2));

	m_EquipmentSelector.HideCursor();

	m_EquipSlotSelector.HideCursor();
}

EquipmentMenuState::~EquipmentMenuState()
{
}

void EquipmentMenuState::OnEnter()
{
	m_Console.ClearBuffer();
}

void EquipmentMenuState::OnExit()
{
	m_Console.ClearBuffer();
}

void EquipmentMenuState::Update()
{
	UpdateIndex();
}

void EquipmentMenuState::Draw()
{
	DrawEquipment();
	DrawPlayerInfo();

	m_MenuSelector.Draw();

	m_EquipSlotSelector.Draw();

	if (!m_bInMenuSelect && !m_bInMenuSelect) {
		DrawStatPrediction();

		m_EquipmentSelector.Draw();
	}

	m_Console.Draw();
}

void EquipmentMenuState::ProcessInputs()
{
	if (m_bInMenuSelect) 
	{
		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE)) 
		{
			m_StateMachine.PopState();

			return;
		}

		m_MenuSelector.ProcessInputs();
	}
	else if (m_bInSlotSelect) 
	{
		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE)) 
		{
			m_MenuSelector.ShowCursor();
			m_EquipSlotSelector.HideCursor();
			m_bInMenuSelect = true;
			m_bInSlotSelect = false;
			m_bRemoveEquipment = false;
			m_Console.ClearBuffer();

			return;
		}

		m_EquipSlotSelector.ProcessInputs();
	}
	else 
	{
		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE)) 
		{
			m_EquipSlotSelector.ShowCursor();
			m_EquipmentSelector.HideCursor();
			m_bInMenuSelect = false;
			m_bInSlotSelect = true;
			m_Console.ClearBuffer();

			return;
		}

		m_EquipmentSelector.ProcessInputs();
	}
}

bool EquipmentMenuState::Exit()
{
	return false;
}
