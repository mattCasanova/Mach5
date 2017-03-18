/******************************************************************************/
/*!
\file   M5StateMachine.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/08

Finite Statemachine base class component
*/
/******************************************************************************/
#include "M5StateMachine.h"

M5StateMachine::M5StateMachine(M5ComponentTypes type):
	M5Component(type),
	m_pCurr(nullptr)
{
}
M5StateMachine::~M5StateMachine(void)
{
}
void M5StateMachine::Update(float dt)
{
	m_pCurr->Update(dt);
}
void M5StateMachine::SetNextState(M5State* pNext)
{
	if(m_pCurr)
		m_pCurr->Exit();
	
	m_pCurr = pNext;
	m_pCurr->Enter();
}