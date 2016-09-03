/******************************************************************************/
/*!
\file   M5Object.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/20

//! Component based Game object used in the Mach 5 Engine
*/
/******************************************************************************/
#ifndef M5GAME_OBJECT_H
#define M5GAME_OBJECT_H

#include "M5Vec2.h"
#include "M5ComponentTypes.h"
#include "M5ArcheTypes.h"
#include <vector>

//Forward Declarations
class M5Component;

//! Component based Game object used in the Mach 5 Engine
class M5Object
{
public:
	M5Object(M5ArcheTypes type);
	~M5Object(void);

	void         Update(float dt);
	void         AddComponent(M5Component* pComponent);
	void         RemoveComponent(M5Component* pComponent);
	void         RemoveAllComponents(void);
	void         RemoveAllComponents(M5ComponentTypes type);
	int          GetID(void) const;
	M5ArcheTypes GetType(void) const;
	M5Object*    Clone(void);

	template<typename T>
	T* GetComponent(M5ComponentTypes type);
	

	M5Vec2       pos;         //!< Position of the Game Object
	M5Vec2       scale;       //!< Size of the Game Object
	M5Vec2       vel;         //!< Velocity of the Game Object
	float        rotation;    //!< Rotation of the Game Object
	float        rotationVel; //!< Rotational Velocity of the Game Object
	bool         isDead;      //!< flag to control when a game object should be destroyed
private:
	typedef std::vector<M5Component*> ComponentVec; //!< Typedef for my Vector of Components
	typedef ComponentVec::iterator VecItor;         //!< Typedef for my container iterator

	ComponentVec m_components;                      //!< Vector of Components to Update
	M5ArcheTypes m_type;                            //!< The ArcheType of the Game Object
	int          m_id;                              //!< Unique ID of the Game Object
	static int   s_objectIDCounter;                 //!< Shared ID counter for all Game Objects 

};
/******************************************************************************/
/*!
Template function to find and Cast the desired component to the correct type.

\param type
The type of component to Find

\return 
A pointer to the correct component type or 0 if it doesn't exist.

*/
/******************************************************************************/
template<typename T>
T* M5Object::GetComponent(M5ComponentTypes type)
{
	size_t size = m_components.size();
	for (size_t i = 0; i < size; ++i)
	{
		if (m_components[i]->GetType() == type)
			return static_cast<T*>(m_components[i]);
	}

	return 0;

}



#endif // M5GAME_OBJECT_H

