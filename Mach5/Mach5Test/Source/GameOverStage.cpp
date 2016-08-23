/******************************************************************************/
/*!
file    GameOverStage.cpp
\author Matt Casanova 
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10


The GameOver stage is really used just to quit.  Since I have an splash 
stage, I make sure to have an quit stage to close resources even though for
the demo it is just used for debug stuff.
*/
/******************************************************************************/
#include "GameOverStage.h"
#include "M5Debug.h"
#include "M5Input.h"
#include "M5Gfx.h"
#include "M5StageMgr.h"
#include "M5App.h"
#include "M5Mtx44.h"
#include "M5Vec2.h"

/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameOverStage::Load(void)
{
  m_texture = M5Gfx::LoadTexture("Textures\\GameOver.tga");
  
}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.
*/
/******************************************************************************/
void GameOverStage::Init(void)
{
  //M5Gfx::SetToOrtho();
  M5Gfx::SetBackgroundColor(0, 0, 0);
}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverStage::Update(float /*dt*/)
{
  M5Vec2 windowSize = M5App::GetResolution();
  if (M5Input::IsAnyTriggered())
    M5StageMgr::Quit();

  M5Mtx44 transform;
  M5Mtx44::MakeTransform(transform, windowSize.y, windowSize.y, 0,
    windowSize.x / 2.0f, windowSize.y / 2.0f, 0);

 // M5Gfx::StartScene();
  M5Gfx::SetTexture(m_texture);
  M5Gfx::Draw(transform);
  //M5Gfx::EndScene();
}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverStage::Shutdown(void)
{
  /*I am now done with the console so I can detroy it.*/
  M5DEBUG_DESTROY_CONSOLE();
}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverStage::Unload(void)
{
  M5Gfx::UnloadTexture(m_texture);
  
}
