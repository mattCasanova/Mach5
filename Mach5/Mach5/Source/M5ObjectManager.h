#ifndef M5OBJECT_MANAGER_H
#define M5OBJECT_MANAGER_H

#include "M5Object.h"
#include <vector>

class M5ObjectManager
{
public:
	static M5ObjectManager(void);
	static ~M5ObjectManager(void);

	static M5Object* CreateObject(void);

private:
	typedef std::vector<M5Object*> ObjectVec;
	typedef ObjectVec::iterator VecItor;

	ObjectVec m_objects;
};


#endif //M5OBJECT_MANAGER