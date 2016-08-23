/******************************************************************************/
/*!
\file   M5ObjectManager.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/22

Class for managing the creation, updating and deletion of game objects.

*/
/******************************************************************************/
#include "M5ObjectManager.h"
#include "M5Object.h"
#include "M5Debug.h"
#include "M5ComponentBuilder.h"
#include "M5Component.h"
#include "M5IniFile.h"
#include <vector>
#include <string>
#include <sstream>

namespace
{
const int START_SIZE = 100;
typedef std::vector<M5Object*> ObjectVec;
typedef ObjectVec::iterator VecItor;

static ObjectVec s_objects;
static M5ComponentFactory s_componentFactory;
}//end unnamed namespace

void M5ObjectManager::Init(void)
{
	s_objects.reserve(START_SIZE);
}
void M5ObjectManager::Shutdown(void)
{
	DestroyAllObjects();
}
void M5ObjectManager::DestroyAllObjects(void)
{
	size_t size = s_objects.size();

	for (size_t i = 0; i < size; ++i)
	{
		delete s_objects[i];
		s_objects[i] = 0;
	}

	s_objects.clear();
}
M5Object* M5ObjectManager::CreateObject(M5ComponentTypes type)
{
	M5Object* pNew = new M5Object;
	pNew->AddComponent(s_componentFactory.Build(type));
	s_objects.push_back(pNew);
	return pNew;
}
void M5ObjectManager::DestroyObject(M5Object* pToDestroy)
{
	VecItor itor = std::find(s_objects.begin(), s_objects.end(), pToDestroy);
	M5DEBUG_ASSERT(itor != s_objects.end(), "Trying to destroy an object that doesn't exist");

	delete *itor;
	std::iter_swap(itor, --s_objects.end());
	s_objects.pop_back();
}
void M5ObjectManager::AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder)
{
	s_componentFactory.AddBuilder(type, pBuilder);
}
void M5ObjectManager::RemoveComponent(M5ComponentTypes type)
{
	s_componentFactory.RemoveBuilder(type);
}
M5Object* M5ObjectManager::AddArchetype(M5ArcheTypes /*type*/, const char* fileName)
{
	M5IniFile file;
	std::string components;
	file.ReadFile(fileName);

	M5Object* pObj = new M5Object;
	file.GetValue("components", components);
	file.GetValue("posX",   pObj->m_position.x);
	file.GetValue("posY",   pObj->m_position.y);
	file.GetValue("scaleX", pObj->m_scale.x);
	file.GetValue("scaleY", pObj->m_scale.y);
	file.GetValue("rot",    pObj->m_rotation);
	
	std::stringstream ss(components);
	std::string name;
	while (ss >> name)
	{
		M5Component* pComp = s_componentFactory.Build(StringToComponent(name));
		pComp->FromFile(file);
		pObj->AddComponent(pComp);
	}

	return pObj;
}