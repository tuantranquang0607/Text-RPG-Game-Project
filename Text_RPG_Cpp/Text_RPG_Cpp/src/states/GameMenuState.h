#pragma once

#include "IState.h"
#include "../Selector.h"

class Party;
class Console;
class StateMachine;
class Keyboard;
class Player;

// GameMenuState class is a derived class of IState (a base class representing a state).
class GameMenuState : public IState
{
private:
	const int PANEL_BARS = 90;
	const int MENU_SIZE = 27;
	const int CLEAR_ROW = 90;
	const int SMALL_PANEL_BAR = 29;

	// References to Party, Console, StateMachine, and Keyboard objects.
	Party& m_Party;
	Console& m_Console;
	StateMachine& m_StateMachine;
	Keyboard& m_Keyboard;

	Selector<> m_MenuSelector;
	Selector<std::shared_ptr<Player>> m_PlayerSelector;

	bool m_bExitGame, m_bInMenuSelect;

	int m_ScreenWidth, m_ScreenHeight, m_CenterScreenW, m_PanelBarX;

	enum class SelectType
	{
		ITEM = 0,
		MAGIC,
		EQUIPMENT,
		STATS,
		ORDER,
		NONE
	};

	SelectType m_eSelectType;

	void DrawPanels();
	void DrawPlayerInfo();

	void OnMenuSelect(int index, std::vector<std::wstring> data);
	void OnPlayerSelect(int index, std::vector<std::shared_ptr<Player>> data);
	void OnDrawPlayerSelect(int x, int y, std::shared_ptr<Player> player);

public:
	// Constructor that initializes references to Party, Console, StateMachine, and Keyboard. Destructor
	GameMenuState(Party& party, Console& console, StateMachine& stateMachine, Keyboard& keyboard);
	~GameMenuState();

	// Virtual functions from IState that are overridden in GameMenuState.
	virtual void OnEnter() override; // Called when entering the state.
	virtual void OnExit() override; // Called when exiting the state.
	virtual void Update() override; // Called every frame to update the state.
	virtual void Draw() override; // Called every frame to draw the state.
	virtual void ProcessInputs() override; // Called to process inputs in the state.

	virtual bool Exit() override; // Called to exit the state.
};
