/******************************************************************************/
/*!
\file   MainMenuStage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/17

The MainMenu in AstroShot
*/
/******************************************************************************/
#ifndef MAIN_MENU_STAGE_H
#define MAIN_MENU_STAGE_H

#include "Core\M5Stage.h"

class MainMenuStage : public M5Stage
{
public:
	MainMenuStage(void);
	~MainMenuStage(void);
	virtual void Init(void);
	virtual void Update(float dt);
	virtual void Shutdown(void);
private:
};

#endif //MAIN_MENU_STAGE_H