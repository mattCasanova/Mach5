/******************************************************************************/
/*!
file   M5GameTimer.cpp
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class: GAM 150
\par    Assignment: Simple 2D Engine
\date   2012/11/29

This file holds the implementation of the GameTime functions.
*/
/******************************************************************************/
#include "M5DebugTools.h"
#include <windows.h>
namespace
{
  /*A struct to store values related to the GameTimer functions.*/
  struct GameTimerData
  {
    LARGE_INTEGER frequency; /*The frequency of the high performance clock*/
    LARGE_INTEGER startTime; /*The start time of the frame*/
    LARGE_INTEGER endTime;   /*The end time of the frame*/
    int targetFPS;           /*The number of frame you want per second*/
    float targetFrameTime;   /*The time each frame should take*/
  };

  const int STARTING_FPS = 120;/*My starting frames per second*/
  /*A static instance of my GameTimerData so share with all of the functions.*/
  GameTimerData timerData;
}

namespace M5Timer
{
/******************************************************************************/
/*!
Allows user to set the target frames per second.  Typically this will be 30
or 60, but could be anything.

\param fps
The target frames per second for the game.
*/
/******************************************************************************/
void SetTargetFPS(int fps)
{
  timerData.targetFPS = fps;
  timerData.targetFrameTime = 1.0f / (float)fps;
}
/******************************************************************************/
/*!
Initializes the values of the timer.  This will be called automatically
when the system initializes.  Students should not call this function.

\attention
Students should not call this function.
*/
/******************************************************************************/
void Init(void)
{
#ifdef _DEBUG
  /*I use this to count how many times this function is called.  It is used only
  error checking*/
  static int functionCounter = 0;
  ++functionCounter;

  M5DEBUG_ASSERT(functionCounter == 1,
    "This function should NOT be called by students.");
#endif

  /*Get high performance clock frequency*/
  QueryPerformanceFrequency(&timerData.frequency);
  /*Set other values to 0*/
  timerData.startTime.QuadPart = 0;
  timerData.endTime.QuadPart = 0;
  SetTargetFPS(STARTING_FPS);
}

/******************************************************************************/
/*!
Clears all data and resources related to the Game Timer. This will be called
automatically when the system is shut down.  Students should not call this
function.

\attention
Students should not call this function.

*/
/******************************************************************************/
void Shutdown(void)
{
#ifdef _DEBUG
  /*I use this to count how many times this function is called.  It is used only
  error checking*/
  static int functionCounter = 0;
  ++functionCounter;

  M5DEBUG_ASSERT(functionCounter == 1,
    "This function should NOT be called by students.");
#endif

  /*Reset all of the data*/
  timerData.frequency.QuadPart = 0;
  timerData.startTime.QuadPart = 0;
  timerData.endTime.QuadPart = 0;

}
/******************************************************************************/
/*!
Gets the clock count at the start of the frame.  Students should not call
this function.

\attention
Students should not call this function.

*/
/******************************************************************************/
void StartFrame(void)
{
  /*Get the clock count for the start of the frame.*/
  QueryPerformanceCounter(&timerData.startTime);
}
/******************************************************************************/
/*!
Gets the clock count at the end of the frame.  This function will then return
the total time the frame took to complete in milliseconds.

\attention
Students should not call this function.

\attention
The function will return frame time in milliseconds.

\return
The total time the frame took to complete in milliseconds.

*/
/******************************************************************************/
float EndFrame(void)
{
  LARGE_INTEGER difference;

  /*Get the clock count for the end of the frame*/
  QueryPerformanceCounter(&timerData.endTime);
  /*Subtract end frame from start frame */
  difference.QuadPart = timerData.endTime.QuadPart - timerData.startTime.QuadPart;
  float time = (float)(difference.QuadPart) / timerData.frequency.QuadPart;
  
  while (time <= timerData.targetFrameTime)
  {
    QueryPerformanceCounter(&timerData.endTime);
    difference.QuadPart = timerData.endTime.QuadPart - timerData.startTime.QuadPart;
    time = (float)(difference.QuadPart) / timerData.frequency.QuadPart;
  }

  /*divide total count by frequency to get frame time In milliseconds*/
  return time;
}
}//end namespace M5Timer

