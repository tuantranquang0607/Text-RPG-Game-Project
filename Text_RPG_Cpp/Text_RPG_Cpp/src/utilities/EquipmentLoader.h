#pragma once

#include "../Equipment.h"
#include "Parser.h"

// Class to load equipment data from a file.
class EquipmentLoader : public Parser<Equipment>
{
private:
	// Filepath to the equipment data file.
	std::string m_sFilepath;

	// Flag to indicate if the loader is for weapons.
	bool m_bWeaponLoader;

	// Function to create weapon properties from an XML element.
	WeaponProperties CreateWeaponProperties(tinyxml2::XMLElement* xmlElement);
	// Function to create armor properties from an XML element.
	ArmorProperties CreateArmorProperties(tinyxml2::XMLElement* xmlElement);
	// Function to create a stat modifier from an XML element.
	StatModifier CreateStatModifier(tinyxml2::XMLElement* xmlElement);

public:
	// Constructor to initialize the loader with a filepath and a flag for weapons.
	EquipmentLoader(const std::string& filepath, bool weapons = true);
	// Destructor.
	~EquipmentLoader();

	// Function to create an equipment object from a file.
	std::shared_ptr<Equipment> CreateObjectFromFile(const std::string& objName) override;
};