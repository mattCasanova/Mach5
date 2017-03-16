/******************************************************************************/
/*!
\file   RandomGoComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Component to find, rotate to and move toward a random location
*/
/******************************************************************************/
#ifndef RANDOM_LOCATION_COMPONENT_H
#define RANDOM_LOCATION_COMPONENT_H

#include "Core\M5Component.h"
#include "Core\M5StateMachine.h"
#include "Core\M5Vec2.h"
#include "RandomGoStates.h"

//! Component to find, rotate to and move toward a random location
class RandomGoComponent : public M5StateMachine
{
public:
	RandomGoComponent(void);
	virtual void FromFile(M5IniFile&);
	virtual RandomGoComponent* Clone(void) const;
	M5State* GetState(RandomGoStates state);

	M5Object* GetM5Object(void);
	float  GetSpeed(void) const;
	float  GetRotationSpeed(void) const;
	M5Vec2 GetTarget(void) const;
	void   SetTarget(const M5Vec2& newTarget);

private:
	float       m_speed;
	float       m_rotateSpeed;
	M5Vec2      m_target;
	FindState   m_findState;
	RotateState m_rotateState;
	GoState     m_goState;
};


#endif // !RANDOM_GO_COMPONENT_H
