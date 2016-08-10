/******************************************************************************/
/*!
\file   GameState1.h
\author Matt Casanova 
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/9

This is a stage in the game demo. This shows some basic features of the 
window and engine.
*/
/******************************************************************************/
#ifndef GAME1_STATE_H
#define GAME1_STATE_H

#include "M5Stage.h"

class Game1Stage : public M5Stage
{
public:
  virtual void Load(void);
  virtual void Init(void);
  virtual void Update(float dt);
  virtual void Shutdown(void);
  virtual void Unload(void);
private:
  static const int   MAX_SIZE = 10;
  bool               m_isFullScreen;
  bool               m_isShowCursor;
  float              m_visableTimer;
  char               m_textAsString[MAX_SIZE];

};

#endif /*GAMESTATE1_H*/