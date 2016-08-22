#ifndef M5OBJECT_MANAGER_H
#define M5OBJECT_MANAGER_H

#include "M5ComponentFactory.h"
#include "M5ComponentTypes.h"
#include <vector>

class M5Object;
class M5ComponentBuilder;


class M5ObjectManager
{
public:
	static void Init(void);
	static void Shutdown(void);
	static M5Object* CreateObject(M5ComponentTypes type);
	static void DestroyObject(M5Object* pToDestroy);
	static void AddComponent(M5ComponentTypes type, M5ComponentBuilder* pBuilder);
	static void RemoveComponent(M5ComponentTypes type);
};


#endif //M5OBJECT_MANAGER