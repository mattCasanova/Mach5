#ifndef M5GAME_OBJECT_H
#define M5GAME_OBJECT_H

#include "M5Vec2.h"
#include "M5ComponentTypes.h"
#include <vector>

//Forward Declarations
class M5Component;


class M5Object
{
public:
	M5Object(void);
	~M5Object(void);
	void Update(float dt);
	void AddComponent(M5Component* pComponent);
	void RemoveComponent(M5Component* pComponent);
	void RemoveAllComponents(M5ComponentTypes type);
	int  GetID(void) const;
	template<typename T>
	T* GetComponent(M5ComponentTypes type);

	M5Vec2       m_position;
	M5Vec2       m_scale;
	M5Vec2       m_velocity;
	float        m_rotation;
private:
	typedef std::vector<M5Component*> ComponentVec;
	typedef ComponentVec::iterator VecItor;


	ComponentVec m_components;
	int          m_id;
};

template<typename T>
T* M5Object::GetComponent(M5ComponentTypes type)
{
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		if(m_components[i]->GetType() == type)
			return static_cast<T*>(m_components[i]);
	}

	return 0;

}



#endif // M5GAME_OBJECT_H

