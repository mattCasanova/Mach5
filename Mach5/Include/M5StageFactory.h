/******************************************************************************/
/*!
\file   M5StageFactory.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

Class for instantiating stages based on a regiestered name/type.

*/
/******************************************************************************/
#ifndef M5STAGE_FACTORY_H
#define M5STAGE_FACTORY_h

#include <unordered_map>
#include "M5GameStages.h"

struct M5Stage;
class M5StageBuilder;


class M5StageFactory
{
public:
  ~M5StageFactory(void);
  void AddBuilder(M5GameStages name, M5StageBuilder* builder);
  void RemoveBuilder(M5GameStages name);
  M5Stage* Build(M5GameStages name);
  void ClearBuilders(void);


private:
  typedef std::unordered_map<M5GameStages, M5StageBuilder*> BuilderMap;
  typedef BuilderMap::iterator MapItor;


  BuilderMap m_builderMap;
};



#endif // M5STAGE_FACTORY_H
