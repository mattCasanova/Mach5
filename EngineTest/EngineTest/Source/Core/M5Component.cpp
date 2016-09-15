/******************************************************************************/
/*!
\file   M5Component.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/18

Base class component for M5Objects

*/
/******************************************************************************/
#include "M5Component.h"

int M5Component::s_componentID = 0;


M5Component::M5Component(M5ComponentTypes type):
	isDead(false),
	m_pObj(0), 
	m_type(type),
	m_id(++s_componentID)
{
}
M5Component::~M5Component(void) 
{
	 //Empty Base Class virtual destructor 
}
void M5Component::FromFile(M5IniFile&)
{
	//empty for the base class
}
void M5Component::SetParent(M5Object* pParent)
{ 
	m_pObj = pParent; 
}
M5ComponentTypes M5Component::GetType(void) const 
{ 
	return m_type; 
}
int M5Component::GetID(void)const 
{ 
	return m_id; 
}