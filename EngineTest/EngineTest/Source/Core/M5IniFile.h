/******************************************************************************/
/*!
\file   M5IniFile.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/16

Class to read from or write to an ini file
*/
/******************************************************************************/
#ifndef M5INI_FILE_H
#define M5INI_FILE_H

#include "M5Debug.h"

#include <map>
#include <string>
#include <sstream>

//! Class to read from or write to an ini file
class M5IniFile
{
public:
	M5IniFile(void);
	void ReadFile(const std::string& fileName);
	//Function to get the data from a section
	template<typename T>
	void GetValue(const std::string& key, T& value) const;
	void SetToSection(const std::string& sectionName);
	
	void AddSection(const std::string& sectionName);
	void AddKeyValue(const std::string& key, const std::string& value);
	void WriteFile(const std::string& fileName) const;
private:
	///Template types 
	typedef std::pair<std::string, std::string>        StringPair;
	typedef std::map<std::string, std::string>         KeyValMap;
	typedef KeyValMap::iterator                        KeyValMapItor;
	typedef KeyValMap::const_iterator                  KeyValMapCItor;
	typedef std::pair<std::string, KeyValMap>          StringMapPair;
	typedef std::map<std::string, KeyValMap>           SectionMap;
	typedef SectionMap::iterator                       SectionMapItor;
	typedef SectionMap::const_iterator                 SectionMapCItor;

	//Functions to parse file
	void SeperateKeyValueFromLine(StringPair& sPair, const std::string& line, size_t& begin, size_t& end) const;
	void GetSectionName(std::string& line, size_t& begin, size_t& end) const;
	void RemoveLeadingSpaces(const std::string& line, size_t& begin, size_t& end) const;
	void RemoveTrailingSpaces(const std::string& line, size_t& begin, size_t& end) const;
	void ParseSectionName(StringMapPair& currSection, std::string& line, size_t& begin, size_t& end);
	void ParseKeyValue(StringMapPair& currSection, std::string& line, size_t& begin, size_t& end);

	SectionMap m_sections;
	KeyValMap* m_currSection;
};
/******************************************************************************/
/*!
Takes a key and returns a value of type int

\param key
The key from the file
\param outInt
The value that will be filled in if the key exists
*/
/******************************************************************************/
template<typename T>
void M5IniFile::GetValue(const std::string& key, T& value) const
{
	KeyValMapCItor itor = m_currSection->find(key);
	M5DEBUG_ASSERT(itor != m_currSection->end(), "Ini Key could not be found");

	std::stringstream ss(itor->second);
	ss >> value;
}
/******************************************************************************/
/*!
Takes a key and returns a value of type int

\param key
The key from the file
\param outInt
The value that will be filled in if the key exists
*/
/******************************************************************************/
template<>
inline void M5IniFile::GetValue(const std::string& key, std::string& value) const
{
	KeyValMapCItor itor = m_currSection->find(key);
	M5DEBUG_ASSERT(itor != m_currSection->end(), "Ini Key could not be found");

	value = itor->second;
}

#endif //M5INI_FILE_H
