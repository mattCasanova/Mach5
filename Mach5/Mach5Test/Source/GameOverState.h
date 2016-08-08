/******************************************************************************/
/*!
\file   GameOverState.h
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6
 
This is a stage for the Mach5 Engine Demo project. This is a good place to 
release resources for anything that was allocated in SplashState. He we just 
quit the game.
*/
/******************************************************************************/
#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

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



#endif /* GAMEOVERSTATE_H */