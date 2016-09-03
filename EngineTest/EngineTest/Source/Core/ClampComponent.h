/******************************************************************************/
/*!
\file   WrapComponent.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

Component to wrap an object in the screen
*/
/******************************************************************************/
#ifndef CLAMP_COMPONENT_H
#define CLAMP_COMPONENT_H
#include "M5Component.h"

class ClampComponent : public M5Component
{
public:
	ClampComponent();
	~ClampComponent();
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
};

#endif //CLAMP_COMPONENT_H

