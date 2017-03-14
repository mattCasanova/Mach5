/******************************************************************************/
/*!
\file   OutsideViewKillComponent.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Removes The parent Game Object if it is outside the view port.  Right now
this only works if the viewport isn't rotated.

TODO: Remove Object from rotated viewport
*/
/******************************************************************************/
#include "OutsideViewKillComponent.h"
#include "M5Gfx.h"
#include "M5Math.h"
#include "M5Object.h"

/******************************************************************************/
/*!
Contructor to set type.
*/
/******************************************************************************/
OutsideViewKillComponent::OutsideViewKillComponent(void) :
	M5Component(CT_OutsideViewKillComponent)
{
}
/******************************************************************************/
/*!
Destructor
*/
/******************************************************************************/
OutsideViewKillComponent::~OutsideViewKillComponent(void)
{
}
/******************************************************************************/
/*!
Sets object to dead if it is outside of the view port.  Right now this only 
works if the viewport isn't rotated.
*/
/******************************************************************************/
void OutsideViewKillComponent::Update(float /*dt*/)
{
	//Save position and half scale to new variables for readability.
	const float HALF = .5f;
	M5Vec2 halfScale = m_pObj->scale * HALF;
	M5Vec2 pos       = m_pObj->pos;

	//Get world extents
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);
	
	//If object is outside of world, mark as dead
	if ( ( (pos.x - halfScale.x) > topRight.x ) || ( (pos.x + halfScale.x) < botLeft.x ) ||
		 ( (pos.y - halfScale.y) > topRight.y ) || ( (pos.y + halfScale.y) < botLeft.y ) )
	{
		m_pObj->isDead = true;
	}

}
/******************************************************************************/
/*!
Virtual constructor for this component
*/
/******************************************************************************/
OutsideViewKillComponent* OutsideViewKillComponent::Clone(void) const
{
	OutsideViewKillComponent* pNew = new OutsideViewKillComponent;
	pNew->m_pObj = m_pObj;
	return pNew;
}