#ifndef M5GAME_OBJECT_H
#define M5GAME_OBJECT_H

#include "M5Vec2.h"
#include "M5ComponentType.h"
#include <vector>

//Forward Declarations
class M5Component;


class M5Object
{
public:
	M5Object(void);
	M5Object(const M5Vec2& pos, const M5Vec2& scale, const M5Vec2& vel, float rotation);
	~M5Object(void);
	void Update(float dt);
	void Kill(void);
	void AddComponent(M5Component* pComponent);
	void RemoveComponent(M5Component* pComponent);
	void RemoveComponent(M5ComponentType type);


public:
	typedef std::vector<M5Component*> ComponentVec;
	typedef ComponentVec::iterator VecItor;


	ComponentVec m_components;
	M5Vec2       m_position;
	M5Vec2       m_scale;
	M5Vec2       m_velocity;
	float        m_rotation;
	bool         m_isDead;
	int          m_id;
};


#endif // M5GAME_OBJECT_H

