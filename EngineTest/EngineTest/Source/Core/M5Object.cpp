#include "M5Object.h"
#include "M5Debug.h"
#include "M5Component.h"
#include <algorithm>

namespace
{
const int START_SIZE = 8;
}

int M5Object::s_objectID = 0;


M5Object::M5Object(M5ArcheTypes type) :
	m_components(),
	m_type(type),
	pos(0, 0),
	scale(1, 1),
	vel(0, 0),
	rotation(0),
	m_id(++s_objectID)
{
	m_components.reserve(START_SIZE);
}
M5Object::~M5Object(void)
{
	RemoveAllComponents();
}
void M5Object::RemoveAllComponents(void)
{
	VecItor itor = m_components.begin();
	VecItor end = m_components.end();
	while (itor != end)
	{
		delete (*itor);
		++itor;
	}
}
void M5Object::Update(float dt)
{
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		m_components[i]->Update(dt);
	}
}
int M5Object::GetID(void) const
{
	return m_id;
}
M5Object* M5Object::Clone(void)
{
	//create new object
	M5Object* pClone = new M5Object(m_type);
	//copy this internal data
	pClone->pos   = pos;
	pClone->vel   = vel;
	pClone->scale = scale;
	pClone->m_id  = ++s_objectID;

	//clone all components
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		M5Component* pComp = m_components[i]->Clone();
		pClone->AddComponent(pComp);
	}

	return pClone;
}
void M5Object::AddComponent(M5Component* pComponent)
{
	VecItor itor = std::find(m_components.begin(), m_components.end(), pComponent);
	M5DEBUG_ASSERT(itor == m_components.end(), "Trying to add a component that already exists");
	pComponent->SetParent(this);
	m_components.push_back(pComponent);
}
void M5Object::RemoveComponent(M5Component* pComponent)
{
	VecItor end = m_components.end();
	VecItor itor = std::find(m_components.begin(), end, pComponent);
	M5DEBUG_ASSERT(itor != end, "Trying to remove a component that doesn't exist");
	std::iter_swap(itor, --end);
	m_components.pop_back();
	pComponent->SetParent(0);
	delete pComponent;

}
void M5Object::RemoveAllComponents(M5ComponentTypes type)
{
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (m_components[i]->GetType() == type)
		{
			delete m_components[i];
			m_components[i] = m_components[size - 1];
			m_components.pop_back();
		}
	}
}
M5ArcheTypes M5Object::GetType(void) const
{
	return m_type;
}