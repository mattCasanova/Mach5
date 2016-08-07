/******************************************************************************/
/*!
file    GameOverState.cpp
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

The GameOver state is really used just to quit.  Since I have an splash 
state, I make sure to have an quit state to close resources even though for
the demo it is just used for debug stuff.
*/
/******************************************************************************/
#include "GameOverState.h"
#include "M5DebugTools.h"
#include "M5Input.h"
#include "M5Graphics.h"
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
The Shutdown state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameOverLoad(void)
{
  gameOverTexture = M5Graphics::LoadTexture("Textures\\GameOver.tga");
  
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.
*/
/******************************************************************************/
void GameOverInit(void)
{
  M5Graphics::SetToOrtho();
  M5Graphics::SetBackgroundColor(
    114.0f / 255.f, /*The amount of red in the logo texture*/
    0.f, 0.f);

}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
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

  M5Graphics::StartDraw();
  M5Graphics::SetTexture(gameOverTexture);
  M5Graphics::Draw(transform);
  M5Graphics::EndDraw();
}
/******************************************************************************/
/*!
The Shutdown state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
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
The Shutdown state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverUnload(void)
{
  M5Graphics::UnloadTexture(gameOverTexture);
  
}
