/******************************************************************************/
/*!
file    SplashStage.cpp
\author Matt Casanova 
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

This is a stage for the Mach5 Engine Demo project. This would be a 
good place to load game data and initialize object you need for your game.
*/
/******************************************************************************/
#include "SplashStage.h"

#include "M5App.h"
#include "M5Debug.h"
#include "M5Math.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5StageMgr.h"
#include "M5Gfx.h"
#include "M5GameStages.h"
#include "M5GameObject.h"
#include "GraphicsComponent.h"


/*Make a struct for my shared stage data*/
namespace
{

  /*The max time to be in this stage*/
const float SPLASH_MAX_TIME = 6.0f;

  /*Create a static variable for data so it can't be used in other files.*/
M5Object obj;
}



/******************************************************************************/
/*!
The load stage will only be called once, when the stage is first entered.
You should load resources that won't need to be changed if the stage is 
restarted.

*/
/******************************************************************************/
void SplashStage::Load(void)
{
  /*Create a debug console*/
  M5DEBUG_CREATE_CONSOLE();
  /*Load the only texture we need for this stage*/
  m_splashTexture = M5Gfx::LoadTexture("Textures\\Mach5Logo.tga");
  m_splashTexture = M5Gfx::LoadTexture("Textures\\Mach5Logo.tga");

  /*All drawing in this stage is in screen space*/
  M5Gfx::SetToOrtho();
}
/******************************************************************************/
/*!
The Init function will be called once when the stage is entered, then again
every time the stage is restarted.  You don't want to load textures here.  Use
this is reset things to initial starting values for the stage.  Here I am also 
using this stage to test my vectors and matricies.

*/
/******************************************************************************/
void SplashStage::Init(void)
{
  //This code will only show in the console if it is active and you 
  //are in debug mode.
  M5DEBUG_PRINT("This is a demo of the different things you can do\n");
  M5DEBUG_PRINT("in the Mach5 Engine.  Play with the demo but you must\n");
  M5DEBUG_PRINT("also inspect the code and comments.\n\n");
  M5DEBUG_PRINT("If you find errors, report to mcasanov@digipen.edu");


  M5Gfx::SetBackgroundColor(0.0f, 0.f, 0.f);

  /*Reset the timer for this stage*/
  m_changeTimer = 0.f;
  GfxComponent* pGfxComp = new GfxComponent;
  pGfxComp->SetTextureID(m_splashTexture);
  obj.AddComponent(pGfxComp);

  M5Vec2 windowSize = M5App::GetResolution();
  obj.m_position.Set(windowSize.x / 2, windowSize.y / 2);
  obj.m_scale.Set(windowSize.x, windowSize.y);
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the 
action, behavoir, drawing and stage changes should happen.
*/
/******************************************************************************/
void SplashStage::Update(float dt)
{
  /*increment timer*/
  m_changeTimer += dt;

  /*Check for time, only be in this stage for the 
  set time*/
  if (m_changeTimer > SPLASH_MAX_TIME)
	  M5StageMgr::Quit();
}
/******************************************************************************/
/*!
This is the shutdown stage.  Use this stage to clean up any resources from 
the init stage.  Since this stage is simple, there is nothing to clean up 
here.

*/
/******************************************************************************/
void SplashStage::Shutdown(void)
{
}
/******************************************************************************/
/*!
This is the unload stage.  Use this stage to clean up any resources from the 
load stage.  Here I need to destroy my console and unload my texture.

*/
/******************************************************************************/
void SplashStage::Unload(void)
{
	//obj.RemoveComponent(CT_GraphicsComponent);
  /*We must unload the texture when we are done with the stage*/
  M5Gfx::UnloadTexture(m_splashTexture);
  //M5Gfx::UnloadTexture(m_splashTexture);
}