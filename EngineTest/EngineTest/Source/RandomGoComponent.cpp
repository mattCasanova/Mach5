/******************************************************************************/
/*!
\file   RandomGoComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Finite Statemachine base class component
*/
/******************************************************************************/
#include "RandomGoComponent.h"
#include "Core\M5IniFile.h"



RandomGoComponent::RandomGoComponent():
	M5StateMachine(CT_RandomGoComponent),
	m_speed(1),
	m_rotateSpeed(1),
	m_findState(this),
	m_rotateState(this),
	m_goState(this)
{
	SetNextState(&m_findState);
}
void RandomGoComponent::FromFile(M5IniFile& iniFile)
{
	iniFile.SetToSection("RandomGoComponent");
	iniFile.GetValue("speed", m_speed);
	iniFile.GetValue("rotationSpeed", m_speed);
}
RandomGoComponent* RandomGoComponent::Clone(void) const
{
	RandomGoComponent* pNew = new RandomGoComponent;
	pNew->m_speed = m_speed;
	pNew->m_rotateSpeed = m_rotateSpeed;
	return pNew;
}
M5State* RandomGoComponent::GetState(RandomGoStates state)
{
	switch (state)
	{
	case RGS_FIND_STATE:
		return &m_findState;
		break;
	case RGS_ROTATE_STATE:
		return &m_rotateState;
		break;
	case RGS_GO_STATE:
		return &m_goState;
		break;
	}

	//In case somethings goes wrong 
	return &m_findState;
}
float RandomGoComponent::GetSpeed(void) const
{
	return m_speed;
}
float RandomGoComponent::GetRotationSpeed(void) const
{
	return m_rotateSpeed;
}
M5Vec2 RandomGoComponent::GetTarget(void) const
{
	return m_target;
}
void RandomGoComponent::SetTarget(const M5Vec2& newTarget)
{
	m_target = newTarget;
}
M5Object* RandomGoComponent::GetM5Object(void)
{
	return m_pObj;
}