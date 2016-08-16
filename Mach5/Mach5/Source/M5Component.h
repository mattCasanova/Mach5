#ifndef M5COMPONENT_H
#define M5COMPONENT_H
#include "M5ComponentType.h"

class M5Object;

class M5Component
{
public:
	M5Component(void) { m_type = CT_INVALID; }
	virtual ~M5Component(void) {}//Empty Base Class destructor
	virtual void Update(float dt) = 0;
	virtual M5Component* Clone(void) = 0;
	void SetParent(M5Object* pParent) { m_pParent = pParent; }
	M5Object* GetParent(void) { return m_pParent; }
	M5ComponentType GetType(void) const { return m_type; }

protected:
	M5Object*   m_pParent;
	M5ComponentType m_type;
};


#endif // M5COMPONENT_H