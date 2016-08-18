/******************************************************************************/
/*!
file    Game1Stage.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/9

This is a stage in the game demo. This shows some basic features of the
window and engine.
*/
/******************************************************************************/
#include "Game1Stage.h"


#include "M5App.h"
#include "M5Input.h"
#include "M5StageMgr.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5Gfx.h"

#include "M5StageTypes.h"
#include <cstdio>

namespace
{
const float MAX_TIME = 5.f;
const float FONT_OFFSET = 4.f;
}


/******************************************************************************/
/*!
We have no resources in this demo stage
*/
/******************************************************************************/
void Game1Stage::Load(void)
{
}
/******************************************************************************/
/*!
Just initialize the values here.
*/
/******************************************************************************/
void Game1Stage::Init(void)
{
  /*Initialize stage data*/
  m_isFullScreen = false;
  m_isShowCursor = true;

  /*give a time greater than 5 seconds so we don't start with an invisible window*/
  m_visableTimer = MAX_TIME + 1.f;
}
/******************************************************************************/
/*!
This is the update.  All of the input and game logic is here for this stage.
*/
/******************************************************************************/
void Game1Stage::Update(float dt)
{
  M5Vec2 mouse;
  M5Vec2 topLeft;
  M5Gfx::GetWorldTopLeft(topLeft);

  /*For our font size*/
  float yOffSet = FONT_OFFSET;

  sprintf_s(m_textAsString, "%f", dt);

  /*Check for input*/
  if (M5Input::IsTriggered(M5_S))
  {
    m_isFullScreen = !m_isFullScreen;
    M5App::SetFullScreen(m_isFullScreen);
  }
  else if (M5Input::IsTriggered(M5_W))
  {
    M5App::ShowWindow(false);
    m_visableTimer = 0.f;
  }
  else if (M5Input::IsTriggered(M5_MOUSE_LEFT))
  {
    m_isShowCursor = !m_isShowCursor;
    M5App::ShowCursor(m_isShowCursor);
  }
  else if (M5Input::IsTriggered(M5_N))
  {
    M5StageMgr::SetNextStage(ST_Game2Stage);
  }

  /*Check for time*/
  if (m_visableTimer < MAX_TIME)
  {
    m_visableTimer += dt;
    if (m_visableTimer > MAX_TIME)
      M5App::ShowWindow(true); /*Reset our windows and view port*/

  }

  /*Make sure drawing is in world space*/
  M5Gfx::SetToPerspective();

  /*Get mouse click in screen space*/
  M5Input::GetMouse(mouse);
  /*Convert into world space*/
  M5Gfx::ConvertScreenToWorld(mouse.x, mouse.y);



  /*Start drawing*/
  M5Gfx::StartScene();

  /*Draw my different text starting at the top corner*/
  M5Gfx::SetTextureColor(0xFFFFFFFF);
  topLeft.y -= yOffSet;
  M5Gfx::WriteText("S: Toggle full screen", topLeft.x, topLeft.y);

  M5Gfx::SetTextureColor(0xFF0000FF);
  topLeft.y -= yOffSet;
  M5Gfx::WriteText("W: Toggle showing the window", topLeft.x, topLeft.y);

  M5Gfx::SetTextureColor(0xFF00FFFF);
  topLeft.y -= yOffSet;
  M5Gfx::WriteText("N: Continue", topLeft.x, topLeft.y);

  /*Draw some text at the mouse position*/
  M5Gfx::SetTextureColor(0xFFFF00FF);
  M5Gfx::WriteText("Click: Toggle cursor", mouse.x, mouse.y);

  M5Gfx::SetToOrtho();
  M5Gfx::WriteText(m_textAsString, 100, 100);

  /*End drawing*/
  M5Gfx::EndScene();

}
/******************************************************************************/
/*!
I don't have any resources to shutdown.

*/
/******************************************************************************/
void Game1Stage::Shutdown(void)
{

}
/******************************************************************************/
/*!
I don't have any textures to unload, but since I changed the color, I reset
the to the default.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void Game1Stage::Unload(void)
{
  /*Reset color*/
  M5Gfx::SetTextureColor(0xFFFFFFFF);
}