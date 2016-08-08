/******************************************************************************/
/*!
file    GameOverStage.cpp
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

The GameOver stage is really used just to quit.  Since I have an splash 
stage, I make sure to have an quit stage to close resources even though for
the demo it is just used for debug stuff.
*/
/******************************************************************************/
#include "GameOverState.h"
#include "M5DebugTools.h"
#include "M5Input.h"
#include "M5Gfx.h"
#include "M5StageMgr.h"
#include "M5App.h"
#include "M5Mtx44.h"
#include "M5Vec2.h"

namespace
{
  int gameOverTexture;
}

/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameOverLoad(void)
{
  gameOverTexture = M5Gfx::LoadTexture("Textures\\GameOver.tga");
  
}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.
*/
/******************************************************************************/
void GameOverInit(void)
{
  M5Gfx::SetToOrtho();
  M5Gfx::SetBackgroundColor(
    114.0f / 255.f, /*The amount of red in the logo texture*/
    0.f, 0.f);

}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverUpdate(float /*dt*/)
{
  M5Vec2 windowSize = M5App::GetResolution();
  if (M5Input::IsAnyTriggered())
    M5StageMgr::Quit();

  M5Mtx44 transform;
  M5Mtx44::MakeTransform(transform, windowSize.y, windowSize.y, 0,
    windowSize.x / 2.0f, windowSize.y / 2.0f, 0);

  M5Gfx::StartScene();
  M5Gfx::SetTexture(gameOverTexture);
  M5Gfx::Draw(transform);
  M5Gfx::EndScene();
}
/******************************************************************************/
/*!
The Shutdown stage is really used just to quit.  Since I have an init 
stage, I make sure to have an quit stage even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverShutdown(void)
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
void GameOverUnload(void)
{
  M5Gfx::UnloadTexture(gameOverTexture);
  
}
