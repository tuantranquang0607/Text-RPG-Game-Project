#include "GameState.h"
#include "StateMachine.h"
#include "../Logger.h"
#include "../Console.h"
#include "../inputs/Keyboard.h"
#include "../Potion.h"
#include "../utilities/ItemCreator.h"

// Constructor for the GameState class
GameState::GameState(Console& console, Keyboard& keyboard, StateMachine& stateMachine) :
	m_Console(console), // Initialize the Console reference
	m_Keyboard(keyboard), // Initialize the Keyboard reference
	m_StateMachine(stateMachine), // Initialize the StateMachine reference
	m_Selector(console, keyboard, { L"Start", L"Settings", L"Exit" }), // Initialize the Selector
	/*m_TestInventory{}*/ // Test to be removed
	m_Party{nullptr} // Initialize the Party pointer to nullptr
{
	// Create a new Player object and assign it to m_TestPlayer
	/*m_TestPlayer = std::make_unique<Player>(L"Test Player", L"text-player", m_TestInventory, 1, 200);*/

	// Create a new Party object and assign it to m_Party
	m_Party = std::make_unique<Party>();

	// Create an item to add to inventory test
	auto potion = ItemCreator::CreateItem(Item::ItemType::HEALTH, L"Health Potion", L"Restores a bit of health", 25, 50);

	m_Party->GetInventory().AddItem(std::move(potion));

	auto sword = ItemCreator::CreateEquipment(
		Equipment::EquipType::WEAPON, 
		WeaponProperties(15, WeaponProperties::WeaponType::SWORD),
		ArmorProperties(),
		StatModifier(3, StatModifier::ModifierType::STRENGTH),
		L"Short Sword", L"A small sword of shabby material.", 100, 50);

	auto chest_armor = ItemCreator::CreateEquipment(
		Equipment::EquipType::ARMOR,
		WeaponProperties(),
		ArmorProperties(10, ArmorProperties::ArmorType::CHEST_BODY),
		StatModifier(3, StatModifier::ModifierType::STRENGTH),
		L"Chest Plate", L"A small chest plate made of iron.", 100, 50);

	m_Party->GetInventory().AddEquipment(std::move(sword));
	m_Party->GetInventory().AddEquipment(std::move(chest_armor));

	// Create a new Player object with the name "Test Player", description "text-player", the Party's inventory, level 1, and 200 health points
	auto player = std::make_shared<Player>(L"Test Player", L"text-player", m_Party->GetInventory(), 1, 200);

	// Add the new Player to the Party
	m_Party->AddMember(std::move(player));
}

GameState::~GameState()
{
}

// Destructor for the GameState class.
void GameState::OnEnter()
{
	// TRPG_LOG("Entered Game State");

	m_Console.ClearBuffer();
}

// Method called when entering the GameState.
void GameState::OnExit()
{
	// Log a message indicating that the game state has been exited.
	// TRPG_LOG("Exit Game State");

	m_Console.ClearBuffer();
}

// Method to update the GameState.
void GameState::Update()
{
	// Log a message indicating that the game state has been updated.
	// TRPG_LOG("Updated Game State");
}

// This function is responsible for drawing the game state on the console.
void GameState::Draw()
{
	// Loop over each member of the party
	for (const auto& member : m_Party->GetParty()) 
	{
		// Get the name of the member
		const auto& name = member->GetName();

		// Convert the member's health points to a string
		std::wstring hp = std::to_wstring(member->GetHP());

		// Convert the member's maximum health points to a string
		std::wstring max_hp = std::to_wstring(member->GetMaxHP());

		// Write the member's name to the console at position (50, 30) in blue color
		m_Console.Write(50, 30, name, BLUE);

		// Write the member's health points and maximum health points to the console at position (50, 32) in blue color
		m_Console.Write(50, 32, L"HP: " + hp + L"/" + max_hp, BLUE);

		// Get the list of the member's stats
		const auto& stats_list = member->GetStats().GetStatList();

		// Initialize a counter for the y-coordinate of the console
		int i = 0;

		// Loop over each stat in the member's stats list
		for (const auto& [stat, value] : stats_list)
		{
			// Get the modifier value of the stat
			const auto& mod_value = member->GetStats().GetModifier(stat);

			// Write the stat's name to the console at position (50, 34 + i)
			m_Console.Write(50, 34 + i, stat + L":");

			// Write the stat's value plus its modifier value to the console at position (70, 34 + i)
			m_Console.Write(70, 34 + i, std::to_wstring(value + mod_value));

			// Increment the counter
			i++;
		}
	}

	// Get the name of the test player.
	/*const auto& name = m_TestPlayer->GetName();*/

	// Convert the current health points of the test player to a string.
	/*std::wstring hp = std::to_wstring(m_TestPlayer->GetHP());*/

	// Convert the maximum health points of the test player to a string.
	/*std::wstring max_hp = std::to_wstring(m_TestPlayer->GetMaxHP());*/

	// Write the name of the test player on the console at position (50, 30) in blue color.
	/*m_Console.Write(50, 30, name, BLUE);*/

	// Write the current and maximum health points of the test player on the console at position (50, 32) in blue color.
	/*m_Console.Write(50, 32, L"HP: " + hp + L"/" + max_hp, BLUE);*/

	// Draw the selector.
	m_Selector.Draw();

	// Draw the console.
	m_Console.Draw();
}

// Method to process inputs in the GameState.
void GameState::ProcessInputs()
{
	// If the escape key was just pressed, pop the current state from the state machine.
	if (m_Keyboard.IsKeyJustPressed(KEY_ESCAPE))
	{
		m_StateMachine.PopState();

		return;
	}

	m_Selector.ProcessInputs();
}

// Method to check if the GameState should be exited. Currently always returns false. 
bool GameState::Exit()
{
	return false;
}
