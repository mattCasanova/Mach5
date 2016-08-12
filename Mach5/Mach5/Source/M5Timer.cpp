/******************************************************************************/
/*!
\file   M5Timer.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

Singleton class to control game time related functions.

*/
/******************************************************************************/
#include "M5Timer.h"
#include "M5Debug.h"
/*! Used to exclude rarely-used stuff from Windows */
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>


namespace
{
LARGE_INTEGER s_frequency;       /*!< The frequency of the high performance clock*/
LARGE_INTEGER s_startTime;       /*!< The start time of the frame*/
LARGE_INTEGER s_endTime;         /*!< The end time of the frame*/
float         s_targetFPS;       /*!< The number of frame you want per second*/
float         s_targetFrameTime; /*!< The time each frame should take*/
}

/******************************************************************************/
/*!
Allows user to set the target frames per second.  Typically this will be 30
or 60, but could be anything.

\param [in] fps
The target frames per second for the game.
*/
/******************************************************************************/
void M5Timer::SetTargetFPS(int fps)
{
  s_targetFPS = static_cast<float>(fps);
  s_targetFrameTime = 1.0f / fps;
}
/******************************************************************************/
/*!
Initializes the values of the timer.  This will be called automatically
when the system initializes. 

\param [in] fps
The target frames per second for the game.
/******************************************************************************/
void M5Timer::Init(int fps)
{
  M5DEBUG_CALL_CHECK(1);

  /*Get high performance clock frequency*/
  QueryPerformanceFrequency(&s_frequency);
  /*Set other values to 0*/
  s_startTime.QuadPart = 0;
  s_endTime.QuadPart = 0;
  SetTargetFPS(fps);
}
/******************************************************************************/
/*!
Gets the clock count at the start of the frame. 
*/
/******************************************************************************/
void M5Timer::StartFrame(void)
{
  /*Get the clock count for the start of the frame.*/
  QueryPerformanceCounter(&s_startTime);
}
/******************************************************************************/
/*!
Gets the clock count at the end of the frame.  This function will then return
the total time the frame took to complete in seconds.

\attention
The function will return frame time in seconds.

\return
The total time the frame took to complete in seconds.

*/
/******************************************************************************/
float M5Timer::EndFrame(void)
{
  LARGE_INTEGER difference;
  float time;

  do 
  {
    /*Get the clock count for the end of the frame*/
    QueryPerformanceCounter(&s_endTime);
    /*Subtract end frame from start frame */
    difference.QuadPart = s_endTime.QuadPart - s_startTime.QuadPart;
    time = static_cast<float>(difference.QuadPart) / s_frequency.QuadPart;
  } while (time < s_targetFrameTime);

  /*divide total count by frequency to get frame time In seconds*/
  return time;
}

