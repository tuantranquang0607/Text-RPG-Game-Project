#include "Actor.h"

// This is the default constructor for the Actor class. It delegates to the parameterized constructor, 
// initializing a new Actor with the name "Actor_name", level 1, maximum health points 100, and type WARRIOR.
Actor::Actor() : Actor( L"Actor_name", 1, 100, ActorType::WARRIOR )
{
}

// This is a constructor for the Actor class that initializes the class with a name, level, maximum health points, and type.
// The experience points are initialized to 0, the experience points to the next level are initialized to 250,
// the health points are initialized to the maximum health points, and the death status is initialized to false.
Actor::Actor(const std::wstring & name, int level, int max_hp, ActorType type) : 
	m_sName{ name },
	m_Level{ level }, 
	m_XP{ 0 }, 
	m_XPToNextLevel{ 250 }, 
	m_HP{ max_hp }, 
	m_MaxHP{ max_hp },
	m_bDead { false },
	m_eActorType{ type }
{
}

// This function increases the health points of the Actor by a specified amount.
// If the resulting health points exceed the maximum health points, the health points are set to the maximum health points.
void Actor::HealHP(int hp)
{
	m_HP += hp;

	if (m_HP >= m_MaxHP)
	{
		m_HP = m_MaxHP;
	}
}

// This function decreases the health points of the Actor by a specified amount.
// If the resulting health points are less than or equal to 0, the health points are set to 0 and the death status is set to true.
void Actor::TakeDamage(int hp)
{
	m_HP -= hp;

	if (m_HP <= 0)
	{
		m_HP = 0;
		m_bDead = true;
	}
}
