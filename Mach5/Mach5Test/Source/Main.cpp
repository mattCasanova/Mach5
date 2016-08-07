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
#include "M5State.h"
#include "M5GameData.h"

/*My GameStates*/
#include "SplashState.h"
#include "GameState1.h"
#include "GameState2.h"
#include "GameOverState.h"

#include "M5DebugTools.h"

/******************************************************************************/
/*!
The user must add states to their game After initializing the Application, and 
before updating the Application.

\attention
To make switching states easier, I add the states in the order they are listed
in the DemoStates enum.
*/
/******************************************************************************/
void DemoAddStates(void)
{
  M5State state;
  int stateID;

  /*A make sure to add my state in the order they are in 
  my DemoStates enum*/

  /*Add my SplashState*/
  state.Load     = SplashStateLoad;
  state.Init     = SplashStateInit;
  state.Update   = SplashStateUpdate;
  state.Shutdown = SplashStateShutdown;
  state.Unload   = SplashStateUnload;

  stateID = M5StageMgr::AddState(state);
  M5StageMgr::SetStartState(stateID);
  
  /*Add my first game state*/
  state.Load     = GameState1Load;
  state.Init     = GameState1Init;
  state.Update   = GameState1Update;
  state.Shutdown = GameState1Shutdown;
  state.Unload   = GameState1Unload;

  M5StageMgr::AddState(state);

  /*Add second game state*/
  state.Load     = GameState2Load;
  state.Init     = GameState2Init;
  state.Update   = GameState2Update;
  state.Shutdown = GameState2Shutdown;
  state.Unload   = GameState2Unload;

  M5StageMgr::AddState(state);

  /*Add my GameOverState*/
  state.Load     = GameOverLoad;
  state.Init     = GameOverInit;
  state.Update   = GameOverUpdate;
  state.Shutdown = GameOverShutdown;
  state.Unload   = GameOverUnload;

  M5StageMgr::AddState(state);
  
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
  /*Function to add all of my game states*/
  DemoAddStates();
  /*Start running the game*/
  M5App::Update();
  /*This function must be called after the window has closed!!!*/
  M5App::Shutdown();
  
  //int* p = new int;
  //p = 0;

  return 0;
}

