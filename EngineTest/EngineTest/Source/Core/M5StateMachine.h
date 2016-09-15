/******************************************************************************/
/*!
\file   M5StateMachine.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Finite Statemachine base class component
*/
/******************************************************************************/
#ifndef M5STATEMACNINE_H
#define M5STATEMACNINE_H

#include "M5Component.h"
#include "M5Vec2.h"

//!< Base State for M5StateMachines
class M5State
{
public:
	virtual ~M5State(void) {}
	virtual void Enter(float dt) = 0;
	virtual void Update(float dt) = 0;
	virtual void Exit(float dt) = 0;
};

//!< Base class for Finite statemanchine component for AstroShot
class M5StateMachine : public M5Component
{
public:
	M5StateMachine(M5ComponentTypes type);
	virtual ~M5StateMachine(void);
	virtual void Update(float dt);
	virtual M5Component* Clone(void) = 0;
	void SetNextState(M5State* pNext);
	void SetStartState(M5State* pStart);
private:
	M5State* m_pCurr;
	M5State* m_pNext;
};

#endif //M5STATEMACNINE_H
