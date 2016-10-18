/******************************************************************************/
/*!
\file   UIButtonComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Component to test if a HUD button is clicked
*/
/******************************************************************************/
#include "UIButtonComponent.h"
#include "M5Command.h"


#include "M5Intersect.h"
#include "M5Input.h"
#include "M5Debug.h"
#include "M5Object.h"
#include "M5IniFile.h"
#include "M5ObjectManager.h"

/******************************************************************************/
/*!
Constructor to Set the type
*/
/******************************************************************************/
UIButtonComponent::UIButtonComponent(void) :
	M5Component(CT_UIButtonComponent), m_pOnClick(nullptr)
{
}
/******************************************************************************/
/*!
Destructor for the UIButton Component
*/
/******************************************************************************/
UIButtonComponent::~UIButtonComponent(void)
{
	delete m_pOnClick;
	m_pOnClick = 0;
}
/******************************************************************************/
/*!
Checks if the button has been clicked in screen space
*/
/******************************************************************************/
void UIButtonComponent::Update(float)
{
	if (M5Input::IsTriggered(M5_MOUSE_LEFT))
	{
		M5Input::GetMouse(m_clickPoint);
		if (M5Intersect::PointRect(m_clickPoint, m_pObj->pos, m_pObj->scale.x, m_pObj->scale.y))
		{
			M5DEBUG_ASSERT(m_pOnClick != 0, "The UIButton command is null");
			m_pOnClick->Execute();
		}
	}
}
/******************************************************************************/
/*!
Sets object to dead if it is outside of the view port.  Right now this only
works if the viewport isn't rotated.
*/
/******************************************************************************/
void UIButtonComponent::FromFile(M5IniFile&)
{
	//iniFile.SetToSection("UIButtonComponent");
	//m_pOnClick = M5ObjectManager::CreateCommand();
}
/******************************************************************************/
/*!
Sets object to dead if it is outside of the view port.  Right now this only
works if the viewport isn't rotated.
*/
/******************************************************************************/
UIButtonComponent* UIButtonComponent::Clone(void) const
{
	UIButtonComponent* pClone = new UIButtonComponent();
	pClone->m_pObj = m_pObj;
	if(pClone->m_pOnClick != nullptr)
	  pClone->m_pOnClick = m_pOnClick->Clone();
	return pClone;
}
/******************************************************************************/
/*!
Sets the command of the given UIButton onClick action, and deletes the old one

\param [in] pCommand
The new command to set
*/
/******************************************************************************/
void UIButtonComponent::SetOnClick(M5Command* pCommand)
{
	//Make sure to delete the old one
	delete m_pOnClick;
	m_pOnClick = pCommand;
}

