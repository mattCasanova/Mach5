/******************************************************************************/
/*!
file    M5StageMgr.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/7

This provides Support for switching stages in your game, such as switching
between levels and menus.
*/
/******************************************************************************/
#include "M5StageMgr.h"
#include "M5App.h"
#include "M5Input.h"
#include "M5GameTimer.h"
#include "M5Stage.h"
#include "M5DebugTools.h"

#include <vector>


namespace
{
//"Private" class data
static std::vector<M5Stage*> s_stages;      /*!< Container to hold my stages*/
static M5GameData*          s_pGameData;    /*!< Pointer to user defined shared data from main*/
static int                  s_currStage;    /*!< This is the current stage we are in*/
static int                  s_prevStage;    /*!< This is the last stage we were in*/
static int                  s_nextStage;    /*!< This is the stage we are going into*/
static bool                 s_isQuitting;   /*!< TRUE if we are quitting, FALSE otherwise*/
static bool                 s_isRestarting; /*!< TRUE if we are restarting, FALSE otherwise*/
static bool                 s_hasAdded;     /*!< Checks if the user has added a stage or not*/

void DefaultLoad(void);
void DefaultInit(void);
void DefaultUpdate(float dt);
void DefaultShutdown(void);
void DefaultUnload(void);

/*!< ID for invalid stage*/
const int INVALID_ID = -1;
/*!< The number of stages my vector can hold at init time.*/
const int STARTING_COUNT = 10;

/*void AddDefaultStage(void)
{
  M5Stage defaultStage;
  defaultStage.Load = DefaultLoad;
  defaultStage.Init = DefaultInit;
  defaultStage.Update = DefaultUpdate;
  defaultStage.Shutdown = DefaultShutdown;
  defaultStage.Unload = DefaultUnload;

  int stageId = M5StageMgr::AddStage(defaultStage);
  s_currStage = s_nextStage = stageId;
  s_hasAdded = false;

}*/
}//end unnamed namespace

/******************************************************************************/
/*!
Allocates recourses related to the Stage Manager.  This should NOT be called
by the user.  It will be called automatically by the system.

\param [in] pGData
A pointer to M5GameData struct to copy initial data.

\param [in] gameDataSize
The size of the M5GameData struct so we know how much memory to allocate.
*/
/******************************************************************************/
void M5StageMgr::Init(const M5GameData* pGData, int gameDataSize)
{
  M5DEBUG_CALL_CHECK(1);

  /*Initialize stage data*/
  s_prevStage = INVALID_ID;
  s_currStage = INVALID_ID;
  s_nextStage = INVALID_ID;
  s_isQuitting = false;
  s_isRestarting = false;
  s_stages.reserve(STARTING_COUNT);

  //AddDefaultStage();

  M5DEBUG_ASSERT(gameDataSize >= 1, "M5GameData must have at least size of 1");

  /*Allocate space for game data, I don't know the details so just copy bytes*/
  s_pGameData = reinterpret_cast<M5GameData*>(new char[gameDataSize]);
  /*Copy all data*/
  std::memcpy(s_pGameData, pGData, (size_t)gameDataSize);
}
/******************************************************************************/
/*!
Deallocates recourses related to the Stage Manager.  This should NOT be called
by the user.  It will be called automatically by the system.

*/
/******************************************************************************/
void M5StageMgr::Shutdown(void)
{
  //clear all added stages
  for (size_t i = 0; i < s_stages.size(); ++i)
    delete s_stages[i];


  //This was allocated as an array of bytes
  char* toDelete = reinterpret_cast<char*>(s_pGameData);
  delete[] toDelete;
  s_pGameData = 0;
}
/******************************************************************************/
/*!
Adds a stage to the Stage manager so that you can change to that stage  later.
The return values of this function are guaranteed to be in numeric order
start from 0.  The value returned is a unique id for this stage.  Use the
id to set start stage and when setting the next stage.

\attention
This function will return stage ids in numeric order 0, 1, 2, 3, 4, ect.

\param [in] stage
A stage struct that contains the init, update, shutdown, Load and UnLoad
functions for a stage.

\return
A unique id for this stage.

*/
/******************************************************************************/
int M5StageMgr::AddStage(M5Stage* stage)
{
  if (!s_hasAdded)
  {
    s_hasAdded = true;
    s_stages.clear();
  }

  /*Add stage to stage array*/
  s_stages.push_back(stage);
  return static_cast<int>(s_stages.size()) - 1;/*The id is the index in the array*/
}
/******************************************************************************/
/*!
Returns if the Game stage manager has been set to quit or not.

\return
TRUE if the manager has been set to quit, FALSE otherwise.

*/
/******************************************************************************/
bool M5StageMgr::IsQuitting(void)
{
  return s_isQuitting;
}
/******************************************************************************/
/*!
Returns if the game stage manager is going to restart the stage or not.

\return
TRUE if the manager is going to restart the stage, FALSE otherwise.

*/
/******************************************************************************/
bool M5StageMgr::IsRestarting(void)
{
  return s_isRestarting;
}
/******************************************************************************/
/*!
Returns the unique id of the previous stage.

\return
The unique id of the previous stage.
*/
/******************************************************************************/
int M5StageMgr::GetPreviousStage(void)
{
  return s_prevStage;
}
/******************************************************************************/
/*!
Returns the unique id of the current stage.

\return
The unique id of the current stage.
*/
/******************************************************************************/
int M5StageMgr::GetCurrentStage(void)
{
  return s_currStage;
}
/******************************************************************************/
/*!
Returns the unique id of the next stage.

\return
The unique id of the next stage.
*/
/******************************************************************************/
int M5StageMgr::GetNextStage(void)
{
  return s_nextStage;
}
/******************************************************************************/
/*!
Returns an Instance of the Shared GameData.

\return
A pointer to the shared GameData
*/
/******************************************************************************/
M5GameData& M5StageMgr::GetGameData(void)
{
  return *s_pGameData;
}
/******************************************************************************/
/*!
This function controls the main game loop.  It will update the application,
initialize, update and shutdown all stages.  This must be called Every
GameLoop.

*/
/******************************************************************************/
void M5StageMgr::Update(void)
{
  float frameTime = 0.0f;
  /*Get the Current stage*/
  M5Stage* pCurrentStage = s_stages[s_currStage];


  /*Only load if we are not restarting*/
  if (s_isRestarting == false)
    pCurrentStage->Load();
  else
    s_isRestarting = false;/*We need to reset our restart flag*/

  /*Call the initialize function*/
  pCurrentStage->Init();

  /*Keep going until the stage has changed or we are quitting.*/
  while ((s_currStage == s_nextStage) && !s_isQuitting && !s_isRestarting)
  {
    /*Our main game loop*/
    M5Timer::StartFrame();/*Save the start time of the frame*/
    M5Input::Reset(frameTime);
    M5App::ProcessMessages();
    pCurrentStage->Update(frameTime);
    frameTime = M5Timer::EndFrame();/*Get the total frame time*/
  }

  /*Make sure to shutdown the stage*/
  pCurrentStage->Shutdown();

  /*Only unload if we are not restarting*/
  if (s_isRestarting == false)
    pCurrentStage->Unload();

  /*Change Stage*/
  ChangeStage();
}
/******************************************************************************/
/*!
Sets the stage that the game should start in.  This should only be called once
at the beginning of the game.

\attention
THIS SHOULD ONLY BE CALLED ONCE AT THE BEGINNING OF THE GAME.

\param [in] startStage
A unique id of the stage that the game should start in.
*/
/******************************************************************************/
void M5StageMgr::SetStartStage(int startStage)
{
  s_prevStage = startStage;
  s_currStage = startStage;
  s_nextStage = startStage;
}
/******************************************************************************/
/*!
Sets the stage id of the next stage.  Use this to request a change from one
stage to another.

\param [in] nextStage
A unique id of the next that the game should start in.
*/
/******************************************************************************/
void M5StageMgr::SetNextStage(int nextStage)
{
  s_nextStage = nextStage;
}
/******************************************************************************/
/*!
Sets if the game stage manager should quit.  Use this to exit the game from
inside a stage.
*/
/******************************************************************************/
void M5StageMgr::Quit(void)
{
  s_isQuitting = true;
}
/******************************************************************************/
/*!
Sets if the game stage manager should restart the current stage.  Use this to
restart the current from inside a stage.

\attention
This does not restart the game.  It calls Shutdown, then Init on the current
stage, and continues updating.
*/
/******************************************************************************/
void M5StageMgr::Restart(void)
{
  s_isRestarting = true;
}
/******************************************************************************/
/*!
Used to change the stage ids after the stage has shutdown.
*/
/******************************************************************************/
void M5StageMgr::ChangeStage(void)
{
  s_prevStage = s_currStage;
  s_currStage = s_nextStage;
}
/*
#include "M5Gfx.h"
#include "M5Input.h"
#include "M5App.h"

namespace
{
const int ARRAY_SIZE = 6;
const float FONT_SIZE = 20;
const char* messages[ARRAY_SIZE] =
{ "You are seeing the default stage for the game",
"You must add your own stages by calling M5StageMgr::AddStage",
"After that, you must set your starting stage by ",
"calling M5StageMgr::SetStartStage\n",
" ",
"Press any key to Quit"
};
void DefaultLoad(void)
{
}
void DefaultInit(void)
{
  M5Gfx::SetToOrtho();
}
void DefaultUpdate(float)
{
  if (M5Input::IsAnyPressed())
    M5StageMgr::Quit();

  M5Vec2 windowSize = M5App::GetResolution();

  M5Gfx::StartScene();
  for (int i = ARRAY_SIZE - 1; i >= 0; --i)
  {
    M5Gfx::WriteText(messages[i], windowSize.x / 3.f,
      windowSize.y / 2.f + FONT_SIZE * (ARRAY_SIZE - i));
  }
  M5Gfx::EndScene();
}
void DefaultShutdown(void)
{
}
void DefaultUnload(void)
{

}*/


