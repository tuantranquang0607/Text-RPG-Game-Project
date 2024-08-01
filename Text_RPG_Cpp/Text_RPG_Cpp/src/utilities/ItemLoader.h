#pragma once

#include "../Item.h"
#include "Parser.h"

// Class for loading items, derived from the Parser class.
class ItemLoader : public Parser<Item>
{
private:
	std::string m_sFilepath; // Filepath for the item definitions.

public:
	ItemLoader(const std::string& filepath); // Constructor that initializes the filepath.
	~ItemLoader();// Destructor for the ItemLoader class.
	
	std::shared_ptr<Item> CreateObjectFromFile(const std::string& objName) override;  // Function to create an item object from the XML file.
};