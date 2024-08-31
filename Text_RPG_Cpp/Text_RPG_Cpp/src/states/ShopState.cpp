#include "ShopState.h"
#include "../Party.h"
#include "../Console.h"
#include "StateMachine.h"
#include "../inputs/Keyboard.h"
#include "../Equipment.h"
#include "../Item.h"
#include "../utilities/ShopLoader.h"
#include "../utilities/ShopParameters.h"
#include "../utilities/ItemCreator.h"
#include "../utilities/trpg_utilities.h"
#include "../Logger.h"

#include <cassert>

using namespace std::placeholders;

ShopState::ShopState(Party& party, Console& console, StateMachine& stateMachine, Keyboard& keyboard, const std::string& shopFilepath) : 
	m_Party(party), 
	m_Console(console), 
	m_StateMachine(stateMachine), 
	m_Keyboard(keyboard), 
	m_pShopParameters{ nullptr }, 
	m_ShopChoiceSelector{ console, keyboard, {L"BUY", L"SELL", L"EXIT"}, SelectorParams{42, 10, 3} }, 
	m_BuySellSelector{ console, keyboard, {L"OK", L"CANCEL"}, SelectorParams{80, 30, 2, 5} }, 
	m_EquipmentSelector{ console, keyboard, std::vector<std::shared_ptr<Equipment>>(), SelectorParams{30, 18, 1, 20, 2} }, 
	m_ItemSelector{ console, keyboard, std::vector<std::shared_ptr<Item>>(), SelectorParams{30, 18, 1, 20, 2} }, 
	m_Quantity{ 0 }, 
	m_Price{ 0 }, 
	m_bInShopSelect{ true }, 
	m_bInItemBuy{ false }, 
	m_bInItemSell{ false }, 
	m_bSetFuncs{ false }, 
	m_bIsEquipmentShop{ false }, 
	m_bBuySellItem{ false }, 
	m_bExitShop{ false }
{
	ShopLoader shopLoader{};
	m_pShopParameters = std::move(shopLoader.CreateShopParametersFromFile(shopFilepath));

	// Check to see if the shop parameters are created
	if (!m_pShopParameters)
	{
		TRPG_ERROR("Failed to load shop parameters from [" + shopFilepath + "]");

		assert(m_pShopParameters);

		m_bExitShop = true;
	}

	switch (m_pShopParameters->shopType)
	{
		case ShopParameters::ShopType::WEAPON:

		case ShopParameters::ShopType::ARMOR:

		case ShopParameters::ShopType::ACCESSORY:
			m_EquipmentSelector.SetData(m_pShopParameters->inventory->GetEquipment());
			m_bIsEquipmentShop = true;

			break;
		case ShopParameters::ShopType::ITEM:

			m_ItemSelector.SetData(m_pShopParameters->inventory->GetItems());
			m_bIsEquipmentShop = false;

			break;
		case ShopParameters::ShopType::NOT_A_SHOP: 
			assert(false && "Shop type must be set for the shop state!"); 

			break;
	}

	m_ShopChoiceSelector.SetSelectionFunc( std::bind(&ShopState::OnShopMenuSelect, this, _1, _2) );
	m_BuySellSelector.SetSelectionFunc( std::bind(&ShopState::BuySellOptions, this, _1, _2) );
	m_BuySellSelector.HideCursor();
}

ShopState::~ShopState()
{
}

void ShopState::OnEnter()
{
}

void ShopState::OnExit()
{
}

void ShopState::Update()
{
	if (m_bExitShop)
	{
		m_StateMachine.PopState();

		return;
	}

	if (m_bBuySellItem)
	{
		UpdateSellQuantity(m_Price);
	}
}

void ShopState::Draw()
{
	DrawShop();

	m_ShopChoiceSelector.Draw();

	// Check if functions are set for buy and sell
	if ((m_bInItemBuy || m_bInItemSell) && m_bSetFuncs)
	{
		if (m_bIsEquipmentShop)
		{
			m_EquipmentSelector.Draw();
		}
		else
		{
			m_ItemSelector.Draw();
		}

		DrawItemsBox();
	}

	if (m_bBuySellItem)
	{
		DrawBuyItems();
		m_BuySellSelector.Draw();
	}

	m_Console.Draw();
}

void ShopState::ProcessInputs()
{
	if (m_bInShopSelect)
	{
		m_ShopChoiceSelector.ProcessInputs();
		return;
	}

	if (m_bInItemBuy && !m_bBuySellItem)
	{
		// Have buy sell functions been set?
		if (!m_bSetFuncs)
		{
			if (m_bIsEquipmentShop)
			{
				m_EquipmentSelector.SetSelectionFunc(std::bind(&ShopState::OnBuyEquipmentSelect, this, _1, _2));
				m_EquipmentSelector.SetDrawFunc(std::bind(&ShopState::RenderBuyEquipment, this, _1, _2, _3));
				m_EquipmentSelector.SetData(m_pShopParameters->inventory->GetEquipment());
			}
			else
			{
				m_ItemSelector.SetSelectionFunc(std::bind(&ShopState::OnBuyItemSelect, this, _1, _2));
				m_ItemSelector.SetDrawFunc(std::bind(&ShopState::RenderBuyItems, this, _1, _2, _3));
				m_ItemSelector.SetData(m_pShopParameters->inventory->GetItems());
			}

			m_bSetFuncs = true;
		}

		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE))
		{
			ResetSelections();

			return;
		}
	}
	else if (m_bInItemSell && !m_bBuySellItem)
	{
		// Have buy sell functions been set?
		if (!m_bSetFuncs)
		{
			if (m_bIsEquipmentShop)
			{
				m_EquipmentSelector.SetSelectionFunc(std::bind(&ShopState::OnSellEquipmentSelect, this, _1, _2));
				m_EquipmentSelector.SetDrawFunc(std::bind(&ShopState::RenderSellEquipment, this, _1, _2, _3));
				m_EquipmentSelector.SetData(m_Party.GetInventory().GetEquipment());
			}
			else
			{
				m_ItemSelector.SetSelectionFunc(std::bind(&ShopState::OnSellItemSelect, this, _1, _2));
				m_ItemSelector.SetDrawFunc(std::bind(&ShopState::RenderSellItems, this, _1, _2, _3));
				m_ItemSelector.SetData(m_Party.GetInventory().GetItems());
			}

			m_bSetFuncs = true;
		}

		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE))
		{
			ResetSelections();

			return;
		}
	}

	if (!m_bBuySellItem && m_bIsEquipmentShop && (m_bInItemBuy || m_bInItemSell))
	{
		m_EquipmentSelector.ProcessInputs();
	}
	else if (!m_bBuySellItem && !m_bIsEquipmentShop && (m_bInItemBuy || m_bInItemSell))
	{
		m_ItemSelector.ProcessInputs();
	}
	else if (m_bBuySellItem)
	{
		m_BuySellSelector.ProcessInputs();
	}
}

bool ShopState::Exit()
{
	return false;
}

void ShopState::DrawShop()
{
}

void ShopState::DrawBuyItems()
{
}

void ShopState::DrawItemsBox()
{
}

void ShopState::ResetSelections()
{
}

void ShopState::OnShopMenuSelect(int index, std::vector<std::wstring> data)
{
}

void ShopState::BuySellOptions(int index, std::vector<std::wstring> data)
{
}

void ShopState::OnBuyItemSelect(int index, std::vector<std::shared_ptr<Item>> data)
{
}

void ShopState::OnBuyEquipmentSelect(int index, std::vector<std::shared_ptr<Equipment>> data)
{
}

void ShopState::OnSellItemSelect(int index, std::vector<std::shared_ptr<Item>> data)
{
	if (index > data.size() - 1 || data.empty())
	{
		return;
	}

	const auto& item = data[index];
	const auto& price = item->GetBuyPrice();

	m_bBuySellItem = true;
	m_BuySellSelector.ShowCursor();
	m_Price = price;
}

void ShopState::OnSellEquipmentSelect(int index, std::vector<std::shared_ptr<Equipment>> data)
{
}

void ShopState::RenderBuyItems(int x, int y, std::shared_ptr<Item> item)
{
	const auto& name = item->GetItemName();
	const auto& price = std::to_wstring(item->GetBuyPrice());

	m_Console.Write(x, y, name);
	m_Console.Write(x + 25, y, price);
}

void ShopState::RenderBuyEquipment(int x, int y, std::shared_ptr<Equipment> item)
{
	const auto& name = item->GetName();
	const auto& price = std::to_wstring(item->GetBuyPrice());

	m_Console.Write(x, y, name);
	m_Console.Write(x + 25, y, price);
}

void ShopState::RenderSellItems(int x, int y, std::shared_ptr<Item> item)
{
}

void ShopState::RenderSellEquipment(int x, int y, std::shared_ptr<Equipment> item)
{
}

void ShopState::UpdateBuyQuantity(int price)
{
	const auto& gold = m_Party.GetGold();

	if (m_Keyboard.IsKeyJustPressed(KEY_W) && gold >= (m_Quantity + 1) * price)
	{
		m_Quantity++;
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_S) && m_Quantity > 0)
	{
		m_Quantity--;
		m_Quantity = std::clamp(m_Quantity, 0, 99);
	}
}

void ShopState::UpdateSellQuantity(int totalAvailable)
{
}
