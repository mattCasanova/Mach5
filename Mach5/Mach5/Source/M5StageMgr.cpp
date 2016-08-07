/******************************************************************************/
/*!
file   M5StageMgr.cpp
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/5

This provides Support for switching states in your game, such as switching
between levels and menus.
*/
/******************************************************************************/
#include "M5StageMgr.h"
#include "M5App.h"
#include "M5Input.h"
#include "M5State.h"
#include "M5DebugTools.h"

#include <vector>


namespace
{
//"Private" class data
static std::vector<M5State> s_states;       /*!< Container to hold my states*/
static M5GameData*          s_pGameData;    /*!< Pointer to user defined shared data from main*/
static int                  s_currState;    /*!< This is the current state we are in*/
static int                  s_prevState;    /*!< This is the last state we were in*/
static int                  s_nextState;    /*!< This is the state we are going into*/
static bool                 s_isQuitting;   /*!< TRUE if we are quitting, FALSE otherwise*/
static bool                 s_isRestarting; /*!< TRUE if we are restarting, FALSE otherwise*/
static bool                 s_hasAdded;     /*!< Checks if the user has added a state or not*/

void DefaultLoad(void);
void DefaultInit(void);
void DefaultUpdate(float dt);
void DefaultShutdown(void);
void DefaultUnload(void);

/*!< ID for invalid state*/
const int INVALID_ID = -1;
/*!< The number of states my vector can hold at init time.*/
const int STARTING_COUNT = 10;

void AddDefaultState(void)
{
  M5State defaultState;
  defaultState.Load = DefaultLoad;
  defaultState.Init = DefaultInit;
  defaultState.Update = DefaultUpdate;
  defaultState.Shutdown = DefaultShutdown;
  defaultState.Unload = DefaultUnload;

  int stateId = M5StageMgr::AddState(defaultState);
  s_currState = s_nextState = stateId;
  s_hasAdded = false;

}
}//end unnamed namespace

/*Prototypes from other files that need to be called here.*/
/*Prototypes for the timer*/
namespace M5Timer
{
void  StartFrame(void);
float EndFrame(void);
}



/******************************************************************************/
/*!
Allocates recourses related to the State Manager.  This should NOT be called
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

  /*Initialize state data*/
  s_prevState = INVALID_ID;
  s_currState = INVALID_ID;
  s_nextState = INVALID_ID;
  s_isQuitting = false;
  s_isRestarting = false;
  s_states.reserve(STARTING_COUNT);

  AddDefaultState();

  M5DEBUG_ASSERT(gameDataSize >= 1, "M5GameData must have at least size of 1");

  /*Allocate space for game data, I don't know the details so just copy bytes*/
  s_pGameData = reinterpret_cast<M5GameData*>(new char[gameDataSize]);
  /*Copy all data*/
  std::memcpy(s_pGameData, pGData, (size_t)gameDataSize);
}
/******************************************************************************/
/*!
Deallocates recourses related to the State Manager.  This should NOT be called
by the user.  It will be called automatically by the system.

*/
/******************************************************************************/
void M5StageMgr::Shutdown(void)
{
  //This was allocated as an array of bytes
  char* toDelete = reinterpret_cast<char*>(s_pGameData);
  delete[] toDelete;
  s_pGameData = 0;
}
/******************************************************************************/
/*!
Adds a state to the State manager so that you can change to that state  later.
The return values of this function are guaranteed to be in numeric order
start from 0.  The value returned is a unique id for this state.  Use the
id to set start state and when setting the next state.

\attention
This function will return state ids in numeric order 0, 1, 2, 3, 4, ect.

\param [in] state
A state struct that contains the init, update, shutdown, Load and UnLoad
functions for a state.

\return
A unique id for this state.

*/
/******************************************************************************/
int M5StageMgr::AddState(const M5State& state)
{
  if (!s_hasAdded)
  {
    s_hasAdded = true;
    s_states.clear();
  }

  /*Add state to state array*/
  s_states.push_back(state);
  return (int)s_states.size() - 1;/*The id is the index in the array*/
}
/******************************************************************************/
/*!
Returns if the Game state manager has been set to quit or not.

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
Returns if the game state manager is going to restart the state or not.

\return
TRUE if the manager is going to restart the state, FALSE otherwise.

*/
/******************************************************************************/
bool M5StageMgr::IsRestarting(void)
{
  return s_isRestarting;
}
/******************************************************************************/
/*!
Returns the unique id of the previous state.

\return
The unique id of the previous state.
*/
/******************************************************************************/
int M5StageMgr::GetPreviousState(void)
{
  return s_prevState;
}
/******************************************************************************/
/*!
Returns the unique id of the current state.

\return
The unique id of the current state.
*/
/******************************************************************************/
int M5StageMgr::GetCurrentState(void)
{
  return s_currState;
}
/******************************************************************************/
/*!
Returns the unique id of the next state.

\return
The unique id of the next state.
*/
/******************************************************************************/
int M5StageMgr::GetNextState(void)
{
  return s_nextState;
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
initialize, update and shutdown all states.  This must be called Every
GameLoop.

*/
/******************************************************************************/
void M5StageMgr::Update(void)
{
  using namespace M5Timer;

  float frameTime = 0.0f;
  /*Get the Current state*/
  M5State* pCurrentState = &s_states[s_currState];


  /*Only load if we are not restarting*/
  if (s_isRestarting == false)
    pCurrentState->Load();
  else
    s_isRestarting = false;/*We need to reset our restart flag*/

  /*Call the initialize function*/
  pCurrentState->Init();

  /*Keep going until the state has changed or we are quitting.*/
  while ((s_currState == s_nextState) && !s_isQuitting && !s_isRestarting)
  {
    /*Our main game loop*/
    StartFrame();/*Save the start time of the frame*/
    M5Input::Reset(frameTime);
    M5App::ProcessMessages();
    pCurrentState->Update(frameTime);
    frameTime = EndFrame();/*Get the total frame time*/
  }

  /*Make sure to shutdown the state*/
  pCurrentState->Shutdown();

  /*Only unload if we are not restarting*/
  if (s_isRestarting == false)
    pCurrentState->Unload();

  /*Change State*/
  ChangeState();
}
/******************************************************************************/
/*!
Sets the state that the game should start in.  This should only be called once
at the beginning of the game.

\attention
THIS SHOULD ONLY BE CALLED ONCE AT THE BEGINNING OF THE GAME.

\param [in] startState
A unique id of the state that the game should start in.
*/
/******************************************************************************/
void M5StageMgr::SetStartState(int startState)
{
  s_prevState = startState;
  s_currState = startState;
  s_nextState = startState;
}
/******************************************************************************/
/*!
Sets the state id of the next state.  Use this to request a change from one
state to another.

\param [in] nextState
A unique id of the next that the game should start in.
*/
/******************************************************************************/
void M5StageMgr::SetNextState(int nextState)
{
  s_nextState = nextState;
}
/******************************************************************************/
/*!
Sets if the game state manager should quit.  Use this to exit the game from
inside a state.
*/
/******************************************************************************/
void M5StageMgr::Quit(void)
{
  s_isQuitting = true;
}
/******************************************************************************/
/*!
Sets if the game state manager should restart the current state.  Use this to
restart the current from inside a state.

\attention
This does not restart the game.  It calls Shutdown, then Init on the current
state, and continues updating.
*/
/******************************************************************************/
void M5StageMgr::Restart(void)
{
  s_isRestarting = true;
}
/******************************************************************************/
/*!
Used to change the state ids after the state has shutdown.
*/
/******************************************************************************/
void M5StageMgr::ChangeState(void)
{
  s_prevState = s_currState;
  s_currState = s_nextState;
}

#include "M5Graphics.h"
#include "M5Input.h"
#include "M5App.h"

namespace
{
const int ARRAY_SIZE = 6;
const float FONT_SIZE = 20;
const char* messages[ARRAY_SIZE] =
{ "You are seeing the default state for the game",
"You must add your own states by calling M5StageMgr::AddState",
"After that, you must set your starting state by ",
"calling M5StageMgr::SetStartState\n",
" ",
"Press any key to Quit"
};
void DefaultLoad(void)
{
}
void DefaultInit(void)
{
  M5Graphics::SetToOrtho();
}
void DefaultUpdate(float /*dt*/)
{
  if (M5Input::IsAnyPressed())
    M5StageMgr::Quit();

  M5Vec2 windowSize = M5App::GetResolution();

  M5Graphics::StartDraw();
  for (int i = ARRAY_SIZE - 1; i >= 0; --i)
  {
    M5Graphics::WriteText(messages[i], windowSize.x / 3.f,
      windowSize.y / 2.f + FONT_SIZE * (ARRAY_SIZE - i));
  }
  M5Graphics::EndDraw();
}
void DefaultShutdown(void)
{
}
void DefaultUnload(void)
{

}
}


