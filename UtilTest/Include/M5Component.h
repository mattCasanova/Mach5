/******************************************************************************/
/*!
\file   M5Component.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/18

Base class component for M5Objects

*/
/******************************************************************************/
#ifndef M5COMPONENT_H
#define M5COMPONENT_H
#include "M5ComponentTypes.h"


class M5Object;
class M5IniFile;

class M5Component
{
public:
	M5Component(void);
	virtual ~M5Component(void);
	virtual void Update(float dt)    = 0;
	virtual M5Component* Clone(void) = 0;
	virtual void FromFile(M5IniFile&) {}//empty for the base class

	void             SetParent(M5Object* pParent);
	M5Object*        GetParent(void);
	M5ComponentTypes GetType(void) const;
	int              GetID(void) const;

protected:
	M5Object*        m_pObj;
	M5ComponentTypes m_type;
private:
	static int       s_componentID;
	int              m_id;
};


#endif // M5COMPONENT_H