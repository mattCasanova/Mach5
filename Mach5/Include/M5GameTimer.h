/******************************************************************************/
/*!
\file   M5GameTimer.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

Singleton class to control game time related functions.

*/
/******************************************************************************/
#ifndef M5GAME_TIMER_H
#define M5GAME_TIMER_H


class M5Timer
{
private:
  friend class M5StageMgr;
  friend class M5App;

  //Initilzes Game Timer data
  static void  Init(int fps);
  //Sets the internal data to the start time of the frame
  static void  StartFrame(void);
  //Calcualates and returns the total frame time in milliseconds
  static float EndFrame(void);
  //Allows the user to 
  static void  SetTargetFPS(int fps);

};


#endif // !M5GAME_TIMER_H
