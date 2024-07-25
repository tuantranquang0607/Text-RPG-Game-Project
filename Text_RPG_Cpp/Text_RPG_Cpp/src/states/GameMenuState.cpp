#include "GameMenuState.h"
#include "../Party.h"
#include "../Console.h"
#include "StateMachine.h"
#include "../inputs/Keyboard.h"
#include "../Player.h"

using namespace std::placeholders;

// DrawPanels() is a method that would be used to draw the panels of the game menu.
void GameMenuState::DrawPanels()
{
}

// DrawPlayerInfo() is a method that displays the player's information on the console. 
// It iterates over each player in the party, checks if the player is active, and if not, 
// it retrieves the player's attributes and displays them.
void GameMenuState::DrawPlayerInfo()
{
	int i = 1;

	for (const auto& player : m_Party.GetParty()) 
	{
		if (player->IsActive()) 
		{
			continue;
		}

		// Get the player attributes
		const auto& name = player->GetName();
		const auto& hp = std::to_wstring(player->GetHP());
		const auto& hp_max = std::to_wstring(player->GetMaxHP());
		const auto& level = std::to_wstring(player->GetLevel());
		const auto& xp = std::to_wstring(player->GetXP());
		const auto& xp_to_next = std::to_wstring(player->GetXPToNextLevel());

		std::wstring hp_string = L"HP: " + hp + L" / " + hp_max;
		std::wstring level_string = L"Lvl: " + level + L" Exp: " + xp + L" / " + xp_to_next;

		m_Console.Write(75, 12 + i, name, LIGHT_AQUA);
		m_Console.Write(75, 13 + i, hp_string, LIGHT_AQUA);
		m_Console.Write(75, 14 + i, level_string, LIGHT_AQUA);
		i += 10;
	}

	// Draw the party Gold
	const auto & gold = std::to_wstring(m_Party.GetGold());
	std::wstring gold_str = L"GOLD: " + gold;
	m_Console.Write(26, 36, gold_str);
}

// OnMenuSelect() is a method that handles the selection of an item from the menu. 
// It uses a switch statement to determine what action to take based on the selected index.
void GameMenuState::OnMenuSelect(int index, std::vector<std::wstring> data)
{
	switch (index) {
	case 0:
		m_eSelectType = SelectType::ITEM;
		break;
	case 1:
		m_eSelectType = SelectType::MAGIC;
		break;
	case 2:
		m_eSelectType = SelectType::EQUIPMENT;
		break;
	case 3:
		m_eSelectType = SelectType::STATS;
		break;
	case 4:
		m_eSelectType = SelectType::ORDER;
		break;
	case 5:
		return;
	case 6:
		m_bExitGame = true;
		return;
	default:
		return;
	}

	// Hide the menu cursor and show the player cursor
	if (m_eSelectType != SelectType::NONE) 
	{
		m_MenuSelector.HideCursor();

		m_PlayerSelector.ShowCursor();

		m_bInMenuSelect = false;
	}
}

// OnPlayerSelect() is a method that handles the selection of a player. 
// It also uses a switch statement to determine what action to take based on the selected index.
void GameMenuState::OnPlayerSelect(int index, std::vector<std::shared_ptr<Player>> data)
{
	const auto& player = data[index];

	switch (m_eSelectType) 
	{
	case SelectType::ITEM:
		
		break;
	case SelectType::MAGIC:
		// TODO: Create new MAGIC State
		break;
	case SelectType::EQUIPMENT:
		
		break;
	case SelectType::STATS:
		
		break;
	case SelectType::ORDER: 

		break;
	default: 
		break;
	}
}

// OnDrawPlayerSelect() is a method that would be used to draw the player selection on the console.
void GameMenuState::OnDrawPlayerSelect(int x, int y, std::shared_ptr<Player> player)
{
}

// The constructor for the GameMenuState class initializes several member variables and sets up the menu and player selectors.
GameMenuState::GameMenuState(Party& party, Console& console, StateMachine& stateMachine, Keyboard& keyboard) :
	m_Party(party),
	m_Console(console),
	m_StateMachine(stateMachine),
	m_Keyboard(keyboard),
	m_MenuSelector
	{
		console,
		keyboard,
		{L"Items", L"Magic", L"Equipment", L"Stat", L"Order", L"Save", L"Exit"},
		SelectorParams{30, 8, 1, 0, 4},
	},
	m_PlayerSelector
	{
		console,
		keyboard,
		std::bind(&GameMenuState::OnPlayerSelect, this, _1, _2),
		std::bind(&GameMenuState::OnDrawPlayerSelect, this, _1, _2, _3),
		party.GetParty(),
		SelectorParams{69, 13, 1, 0, 10},
	},
	m_bExitGame{ false },
	m_bInMenuSelect{ true },
	m_ScreenWidth{ console.GetScreenWidth() },
	m_ScreenHeight{ console.GetScreenHeight() },
	m_CenterScreenW{console.GetHalfWidth()},
	m_PanelBarX{m_CenterScreenW - (PANEL_BARS / 2)},
	m_eSelectType{SelectType::NONE}
{
	m_MenuSelector.SetSelectionFunc(std::bind(&GameMenuState::OnMenuSelect, this, _1, _2));
}

// The destructor for the GameMenuState class doesn't appear to do anything in this code.
GameMenuState::~GameMenuState()
{
}

// OnEnter() and OnExit() are methods that are called when entering and exiting the game menu state. 
// They clear the console buffer and hide the cursor if necessary.
void GameMenuState::OnEnter()
{
	m_Console.ClearBuffer();
}

// Update() is a method that would be used to update the game state.
void GameMenuState::OnExit()
{
	if (m_bInMenuSelect) 
	{
		m_PlayerSelector.HideCursor();
	}

	m_Console.ClearBuffer();
}

// Draw() is a method that draws the game state on the console.
void GameMenuState::Update()
{
}

// Draw() is a method that draws the game state on the console.
void GameMenuState::Draw()
{
	DrawPanels();
	DrawPlayerInfo();

	m_MenuSelector.Draw();
	m_PlayerSelector.Draw();

	m_Console.Draw();
}

// ProcessInputs() is a method that processes user inputs. 
// It checks if the backspace key was pressed and either pops the state or hides the cursor and clears the buffer as necessary.
void GameMenuState::ProcessInputs()
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
	else {
		if (m_Keyboard.IsKeyJustPressed(KEY_BACKSPACE)) 
		{
			m_PlayerSelector.HideCursor();
			m_bInMenuSelect = true;
			m_eSelectType = SelectType::NONE;
			m_MenuSelector.ShowCursor();
			m_Console.ClearBuffer();
			return;
		}

		m_PlayerSelector.ProcessInputs();
	}
}

// Exit() is a method that returns a boolean indicating whether the game should exit.
bool GameMenuState::Exit()
{
	return m_bExitGame;
}
