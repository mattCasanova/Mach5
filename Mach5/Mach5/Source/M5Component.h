#ifndef M5COMPONENT_H
#define M5COMPONENT_H
#include "M5ComponentType.h"

class M5GameObject;

class M5Component
{
public:
	M5Component(void) { m_type = CT_INVALID; }
	virtual ~M5Component(void) {}//Empty Base Class destructor
	virtual void Update(float dt) = 0;
	virtual M5Component* Clone(void) = 0;
	void SetParent(M5GameObject* pParent) { m_pParent = pParent; }
	M5GameObject* GetParent(void) { return m_pParent; }
	M5ComponentType GetType(void) const { return m_type; }

protected:
	M5GameObject*   m_pParent;
	M5ComponentType m_type;
};


#endif // M5COMPONENT_H