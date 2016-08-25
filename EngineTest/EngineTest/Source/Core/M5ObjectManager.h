/******************************************************************************/
/*!
\file   M5ObjectManager.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/22

Globally accessible static class for easy creation and destruction of
game objects.
*/
/******************************************************************************/
#ifndef M5OBJECT_MANAGER_H
#define M5OBJECT_MANAGER_H

#include "M5ComponentFactory.h"
#include "M5ComponentTypes.h"
#include "M5ArcheTypes.h"

class M5Object;
class M5ComponentBuilder;


class M5ObjectManager
{
public:
	friend class M5App;


	static M5Object* CreateObject(M5ArcheTypes type);
	static void DestroyObject(M5Object* pToDestroy);
	static void DestroyAllObjects(void);
	static void DestroyAllObjects(M5ArcheTypes type);
	static void AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder);
	static void RemoveComponent(M5ComponentTypes type);
	static void AddArcheType(M5ArcheTypes type, const char* fileName);
	static void RemoveArcheType(M5ArcheTypes type);
private:
	static void Init(void);
	static void Shutdown(void);
};


#endif //M5OBJECT_MANAGER