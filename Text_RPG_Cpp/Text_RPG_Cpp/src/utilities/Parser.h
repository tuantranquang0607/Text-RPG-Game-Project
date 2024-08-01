#pragma once

#include <tinyxml2.h>
#include <string>
#include <memory>

// Template class for parsing XML files.
template <typename T>
class Parser
{
protected:
	std::unique_ptr<tinyxml2::XMLDocument> m_pXMLDoc; // Unique pointer to an XML document.

public:
	virtual ~Parser() {}; // Virtual destructor for the Parser class.

	// Function to load an XML file.
	tinyxml2::XMLError LoadFile(const std::string& filepath) 
	{
		return m_pXMLDoc->LoadFile(filepath.c_str());
	}

	virtual std::shared_ptr<T> CreateObjectFromFile(const std::string& objname) = 0; // Pure virtual function to create an object from the XML file.

};