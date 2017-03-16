/******************************************************************************/
/*!
\file   RandomGoStates.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2017/03/15

All of the States for the RandomGoComponent Statemachine.
*/
/******************************************************************************/
#ifndef RANDOM_LOCATION_STATES_H
#define RANDOM_LOCATION_STATES_H

#include "Core\M5StateMachine.h"

//Forward Declaration
class RandomGoComponent;
class M5Object;

enum RandomGoStates
{
	RGS_FIND_STATE,
	RGS_ROTATE_STATE,
	RGS_GO_STATE
};

class FindState : public M5State
{
public:
	FindState(RandomGoComponent* parent);
	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();
private:
	RandomGoComponent* m_parent;
};
class RotateState : public M5State
{
public:
	RotateState(RandomGoComponent* parent);
	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();
private:
	float m_targetRot;
	M5Vec2 m_dir;
	RandomGoComponent* m_parent;
};
class GoState : public M5State
{
public:
	GoState(RandomGoComponent* parent);
	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();
private:
	RandomGoComponent* m_parent;
};

#endif