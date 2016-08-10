/******************************************************************************/
/*!
\file   Main.cpp
\author Matt Casanova 
\par    email: lazersquad@gmail.com
\par    Simple 2D Game Engine
\date   2012/11/26

This is file contains the main function to make a basic window. 
*/
/******************************************************************************/
/* These are necessary includes to do any memory leak detection ***************/
/*This should always  be the first code in your file*/
#if defined(DEBUG) | defined(_DEBUG) 
#define CRTDBG_MAP_ALLOC 
#include <cstdlib>
#include <crtdbg.h>
#endif 
/******************************************************************************/

#include <windows.h> /*WinMain*/ 

/*Include the engine functions*/
#include "M5App.h"
#include "M5StageMgr.h"
#include "M5Stage.h"
#include "M5GameData.h"

/*My GameStages*/
#include "M5TemplateBuilder.h"
#include "SplashStage.h"
#include "Game1Stage.h"
#include "Game2Stage.h"
#include "GameOverStage.h"

#include "M5Debug.h"

/******************************************************************************/
/*!
The user must add stages to their game After initializing the Application, and 
before updating the Application.

\attention
To make switching stages easier, I add the stages in the order they are listed
in the DemoStages enum.
*/
/******************************************************************************/
void DemoAddStages(void)
{
  /*Add my Game1Stage*/
  M5StageMgr::AddStage(GS_SplashStage, new M5TemplateBuilder<SplashStage>());
  M5StageMgr::SetStartStage(GS_SplashStage);
  /*Add my Game1Stage*/
  M5StageMgr::AddStage(GS_Game1Stage, new M5TemplateBuilder<Game1Stage>());
  /*Add my Game2Stage*/
  M5StageMgr::AddStage(GS_Game2Stage, new M5TemplateBuilder<Game2Stage>());
  /*Add my GameOverStage*/
  M5StageMgr::AddStage(GS_GameOverStage, new M5TemplateBuilder<GameOverStage>());
}
/******************************************************************************/
/*!

\brief
The main function for a windowed program.

\param instance 
An identifier for the process.  This is used for various windows things.

\param prev
This is not used anymore, we can ignore it.

\param comamndLine
A string that is comes from the typed command line.  In games we usually don't
care.

\param show 
A variable stating if the window is visible, we always want it visible.

\return
An Error code.  Just return 0;
*/
/******************************************************************************/
#pragma warning(suppress: 28251)
int WINAPI WinMain(HINSTANCE instance,
                   HINSTANCE /*prev*/, 
                   LPSTR /*commandLine*/, 
                   int /*show*/)
{
  /*This should appear at the top of winmain to have windws find memory leaks*/
  M5DEBUG_LEAK_CHECKS(-1);


  /*Declare my InitStruct*/
  M5InitData initData;
  /*Create my game data initial values*/
  M5GameData gameData = { 0 };

  /*Set up my InitStruct*/
  initData.instance   = instance;
  initData.width      = 1280;
  initData.height     = 720;
  initData.title      = "MyFirstWindow";
  initData.fps        = 60;
  initData.fullScreen = false;

  /*Information about your specific gamedata */
  initData.pGData       = &gameData;
  initData.gameDataSize = sizeof(M5GameData);

  /*Pass InitStruct to Function.  This function must be called first!!!*/
  M5App::Init(initData);
  /*Function to add all of my game stages*/
  DemoAddStages();
  /*Start running the game*/
  M5App::Update();
  /*This function must be called after the window has closed!!!*/
  M5App::Shutdown();
  
  //int* p = new int;
  //p = 0;

  return 0;
}

