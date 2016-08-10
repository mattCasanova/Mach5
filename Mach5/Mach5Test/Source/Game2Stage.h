/******************************************************************************/
/*!
\file   GameState2.h
\author Matt Casanova 
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/9


This is a stage in the game demo.
*/
/******************************************************************************/
#ifndef GAME2_STAGE_H
#define GAME2_STAGE_H

#include "M5Stage.h"

class Game2Stage : public M5Stage
{
public:
  virtual void Load(void);
  virtual void Init(void);
  virtual void Update(float dt);
  virtual void Shutdown(void);
  virtual void Unload(void);
private:
  int   m_charTexture;
  int   m_hudTexture;
  int   m_bgTexture;
  float m_cameraZ;
  float m_cameraX;
  float m_cameraY;
  float m_cameraRot;
  float m_rotation;
  float m_textcoord;
  float m_totalTime;
  float m_viewTimer;
};

#endif /*GAMESTAGE2_H*/