/******************************************************************************/
/*!
file   DemoStage1.c
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

This is a stage for the Mach5 Engine Demo project. The init stage would be a 
good place to load game data and initialize the random number 
generator. For the demo we are testing our math functions.
*/
/******************************************************************************/
#include "SplashState.h"

#include "M5App.h"
#include "M5DebugTools.h"
#include "M5Math.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5StageMgr.h"
#include "M5Gfx.h"
#include "DemoStates.h"

#include <cstdio>

/*Make a struct for my shared stage data*/
namespace
{

  /*The max time to be in this stage*/
const float SPLASH_MAX_TIME = 6.0f;
const float FONT_SPACING    = 20.f;
const int   ARRAY_SIZE = 20;

  /*Create a static variable for data so it can't be used in other files.*/
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
}
/******************************************************************************/
/*!
The update function will be called once per frame.  This is where all the 
action, behavoir, drawing and stage changes should happen.
*/
/******************************************************************************/
void SplashStage::Update(float dt)
{
  M5Mtx44 transform;
  char timeAsText[ARRAY_SIZE];
  M5Vec2 windowSize = M5App::GetResolution();


  /*increment timer*/
  m_changeTimer += dt;

  //Save my time as a string.
  sprintf_s(timeAsText, "%.2f", SPLASH_MAX_TIME - m_changeTimer);

  /*Check for time, only be in this stage for the 
  set time*/
  if (m_changeTimer > SPLASH_MAX_TIME)
    M5StageMgr::SetNextStage(DS_GAME1);

  /*Set position scale and rotation of what I want to draw*/
  M5Mtx44::MakeTransform(transform, 
    windowSize.x,
    windowSize.y,
    0.0f,
    windowSize.x  / 2,
    windowSize.y / 2,
    0.0);

  /*This must be called before any drawing in the frame.*/
  M5Gfx::StartScene();

  /*Set the image to draw*/
  M5Gfx::SetTexture(m_splashTexture);

  //Once we have set the texture we can draw it with a transform
  M5Gfx::Draw(transform);

  //You can write text too, but this is VERY slow and is best used for debug
  //You cannot control the size of the font, really just use it for debug.
  M5Gfx::WriteText("Splash Screen Time: ", windowSize.x / 3.0f , FONT_SPACING);
  M5Gfx::WriteText(timeAsText, windowSize.x /2.0f + FONT_SPACING , FONT_SPACING);

  //This text will only appear on screen in debug mode.  This is how you 
  //should use the WriteText Function
  M5DEBUG_WRITETEXT("This string will only appear in debug!", windowSize.x / 3.0f,
    windowSize.y*.85f);
  
  
  /*This must be called to after all drawing is completed*/
  M5Gfx::EndScene();
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
  /*We must unload the texture when we are done with the stage*/
  M5Gfx::UnloadTexture(m_splashTexture);
}
