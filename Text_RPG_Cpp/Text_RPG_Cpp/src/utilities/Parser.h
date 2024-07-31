#pragma once

#include <tinyxml2.h>
#include <string>
#include <memory>

template <typename T>
class Parser
{
protected:
	std::unique_ptr<tinyxml2::XMLDocument> m_pXMLDoc;

public:
	virtual ~Parser() {};

	tinyxml2::XMLError LoadFile(const std::string& filepath)
	{
		return m_pXMLDoc->LoadFile(filepath.c_str());
	}

	virtual std::shared_ptr<T> CreateObjectFromFile(const std::string& objname) = 0;

};