#include "GameState.h"
#include "StateMachine.h"
#include "../Logger.h"
#include "../Console.h"
#include "../inputs/Keyboard.h"
#include "../Potion.h"
#include "../utilities/ItemCreator.h"
#include "GameMenuState.h"
#include "../utilities/ItemLoader.h"
#include "../utilities/EquipmentLoader.h"
#include "../utilities/ShopLoader.h"
#include "ShopState.h"

#include <cassert>

// Constructor for the GameState class
GameState::GameState(Console& console, Keyboard& keyboard, StateMachine& stateMachine) :
	m_Console(console), // Initialize the Console reference
	m_Keyboard(keyboard), // Initialize the Keyboard reference
	m_StateMachine(stateMachine), // Initialize the StateMachine reference
	m_Selector(console, keyboard, { L"Start", L"Settings", L"Exit" }), // Initialize the Selector
	m_Party{nullptr}, // Initialize the Party pointer to nullptr
	m_Timer{}, // Initialize the Timer
	m_TypeWriter{ console,
				  45,
				  15,
				  L"This is the new Typewriter\n"
				  L"The Typewriter will be used for various dialogs within the game!"
				  L"The Typewriter will be used for various dialogs within the game!"
				  L"The Typewriter will be used for various dialogs within the game!"
				  L"The Typewriter will be used for various dialogs within the game!"
				  L"The Typewriter will be used for various dialogs within the game!"
				  L"We will also use this for talking and yadda yadda?",
				  60,
				  50,
				  WHITE,
				  BLUE } // Initialize the Typewriter
{
	// Create a new Party object and assign it to m_Party
	m_Party = std::make_unique<Party>();

	// This line creates a health potion item with the name "Health Potion", a description "Restores a bit of health", a health value of 25, and a buy price of 50.
	auto potion = ItemCreator::CreateItem(Item::ItemType::HEALTH, L"Health Potion", L"Restores a bit of health", 25, 50);

	// This line adds the created potion to the inventory of the party.
	m_Party->GetInventory().AddItem(std::move(potion));

	// This line creates a sword equipment with a damage value of 15, a strength modifier of 3, the name "Short Sword", a description "A small sword of shabby material.", a value of 100, and a buy price of 50.
	auto sword = ItemCreator::CreateEquipment(
		Equipment::EquipType::WEAPON, 
		WeaponProperties(15, WeaponProperties::WeaponType::SWORD),
		ArmorProperties(),
		StatModifier(3, StatModifier::ModifierType::STRENGTH),
		L"Short Sword", L"A small sword of shabby material.", 10);

	// This line creates a chest armor equipment with a defense value of 10, a strength modifier of 3, the name "Chest Plate", a description "A small chest plate made of iron.", a value of 100, and a buy price of 50.
	auto chest_armor = ItemCreator::CreateEquipment(
		Equipment::EquipType::ARMOR,
		WeaponProperties(),
		ArmorProperties(10, ArmorProperties::ArmorType::CHEST_BODY),
		StatModifier(3, StatModifier::ModifierType::STRENGTH),
		L"Chest Plate", L"A small chest plate made of iron.", 100);

	// These lines add the created sword and chest armor to the equipment inventory of the party.
	m_Party->GetInventory().AddEquipment(std::move(sword));
	m_Party->GetInventory().AddEquipment(std::move(chest_armor));

	// Create a new Player object with the name "Test Player", description "text-player", the Party's inventory, level 1, and 200 health points
	auto player = std::make_shared<Player>(L"Test Player", L"text-player", m_Party->GetInventory(), 1, 200);
	auto Tuan = std::make_shared<Player>(L"Tuan King of Erdland", L"warrior", m_Party->GetInventory(), 1, 200);

	// Add the new Player to the Party
	m_Party->AddMember(std::move(player));
	m_Party->AddMember(std::move(Tuan));
}

// Destructor for the GameState class.
GameState::~GameState()
{
}

// Destructor for the GameState class.
void GameState::OnEnter()
{
	m_Console.ClearBuffer();  // Clear the console buffer.

	EquipmentLoader el{ "./assets/xml_files/WeaponDefs.xml" }; // Create an EquipmentLoader object with the specified XML file

	auto equipment = el.CreateObjectFromFile("Broad Sword"); // Create an equipment object from the file using the name "Broad Sword"

	assert(equipment); // Ensure that the equipment object was successfully created
}

// Method called when entering the GameState.
void GameState::OnExit()
{
	m_Console.ClearBuffer(); // Clear the console buffer.
}

// Method to update the GameState.
void GameState::Update()
{
	m_TypeWriter.UpdateText(); // Update the text in the Typewriter object.
}

// This function is responsible for drawing the game state on the console.
void GameState::Draw()
{
	// Draw the timer.
	std::wstring time_ms = L"MS: " + std::to_wstring(m_Timer.ElapsedMS());
	std::wstring time_sec = L"SEC: " + std::to_wstring(m_Timer.ElapsedSec());

	// Write the timer to the console at position (25, 25) and (25, 26) in red color
	m_Console.Write(25, 25, time_ms, RED);
	m_Console.Write(25, 26, time_sec, RED);

	// Draw the selector.
	m_Selector.Draw();

	// Draw the Typewriter object.
	m_TypeWriter.Draw(); 

	// Draw the console.
	m_Console.Draw();
}

// Method to process inputs in the GameState.
void GameState::ProcessInputs()
{
	// If the escape key was just pressed, pop the current state from the state machine.
	// This will end the current game state and return to the previous state.
	if (m_Keyboard.IsKeyJustPressed(KEY_ESCAPE))
	{
		m_StateMachine.PopState();

		return;
	}

	// If the 'M' key was just pressed, push a new GameMenuState onto the state machine.
	// This will pause the current game state and switch to the game menu state.
	if (m_Keyboard.IsKeyJustPressed(KEY_M)) 
	{
		m_StateMachine.PushState(std::make_unique<GameMenuState>(*m_Party, m_Console, m_StateMachine, m_Keyboard));

		return;
	}

	if (m_Keyboard.IsKeyJustPressed(KEY_ENTER))
	{
		m_StateMachine.PushState(std::make_unique<ShopState>( *m_Party, m_Console, m_StateMachine, m_Keyboard, "./assets/xml_files/WeaponShopDef.xml" ));

		return;
	}

	// This code is handling keyboard inputs to control a timer.
	if (m_Keyboard.IsKeyJustPressed(KEY_ENTER))
	{
		m_Timer.Start();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_T))
	{
		m_Timer.Stop();
		m_Console.ClearBuffer();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_P))
	{
		m_Timer.Pause();
	}
	else if (m_Keyboard.IsKeyJustPressed(KEY_R))
	{
		m_Timer.Resume();
	}

	// Process inputs for the selector object.
	// This could involve moving a cursor, making a selection, etc., depending on how the Selector class is defined.
	m_Selector.ProcessInputs();
}

// Method to check if the GameState should be exited. Currently always returns false. 
bool GameState::Exit()
{
	return false;
}
