/******************************************************************************/
/*!
\file   GameOverState.h
\author Matt Casanova 
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/9
 
This is a stage for the Mach5 Engine Demo project. This is a good place to 
release resources for anything that was allocated in SplashState. He we just 
quit the game.
*/
/******************************************************************************/
#ifndef GAMEOVERSTAGE_H
#define GAMEOVERSTAGE_H

#include "M5Stage.h"

class GameOverStage : public M5Stage
{
public:
  virtual void Load(void);
  virtual void Init(void);
  virtual void Update(float dt);
  virtual void Shutdown(void);
  virtual void Unload(void);
private:
  int m_texture;
};



#endif /* GAMEOVERSTAGE_H */