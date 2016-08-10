/******************************************************************************/
/*!
\file   M5StageFactory.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

Class for instantiating stages based on a regiestered name/type.

*/
/******************************************************************************/
#include "M5StageFactory.h"
#include "M5Debug.h"
#include "M5Stage.h"
#include "M5StageBuilder.h"

M5StageFactory::~M5StageFactory(void)
{
  ClearBuilders();
}
void M5StageFactory::AddBuilder(M5GameStages name, M5StageBuilder* builder)
{
  std::pair<MapItor, bool> itor = m_builderMap.insert(std::make_pair(name, builder));
  M5DEBUG_ASSERT(itor.second == true, "Trying to add a builder that already exists");
}
void M5StageFactory::RemoveBuilder(M5GameStages name)
{
  size_t removeCount = m_builderMap.erase(name);
  M5DEBUG_ASSERT(removeCount == 0, "Trying to Remove a Builder that doesn't exist");
}
M5Stage* M5StageFactory::Build(M5GameStages name)
{
  MapItor itor = m_builderMap.find(name);
  M5DEBUG_ASSERT(itor != m_builderMap.end(), "Trying to use a Builder that doesn't exist");
  return itor->second->Build();
}
void M5StageFactory::ClearBuilders(void)
{
  MapItor itor = m_builderMap.begin();
  MapItor end  = m_builderMap.end();

  //Make sure to delete all builder pointers first
  while (itor != end)
  {
    delete itor->second;
    itor->second = 0;
    ++itor;
  }

  //Then clear the hash table
  m_builderMap.clear();
}