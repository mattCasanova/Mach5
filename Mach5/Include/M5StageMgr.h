/******************************************************************************/
/*!
\file   M5StageMgr.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/7

Singleton to control quitting, restarting and switching stages.

*/
/******************************************************************************/
#ifndef M5_STAGEMGR_H
#define M5_STAGEMGR_H

//Forward Declarations
struct M5Stage;
struct M5GameData;
class M5StageBuilder;

#include "M5GameStages.h"


//! Singleton to control quitting, restarting and switching stages.
class M5StageMgr
{
public:
  friend class M5App;

  //Adds a stage the the StageMgr
  static int  AddStage(M5Stage* stage);
  static void AddStage(M5GameStages name, M5StageBuilder* builder);
  //Sets the given stage ID to the starting stage of the game
  static void SetStartStage(M5GameStages startStage);
  //Test if the game is quitting
  static bool IsQuitting(void);
  //Test stage is restarting
  static bool IsRestarting(void);
  //Gets the previous stage of the game
  static int  GetPreviousStage(void);
  //Gets the Current Stage of the game
  static int  GetCurrentStage(void);
  //Gets the Next stage of the game
  static int  GetNextStage(void);
  //Gets the pointer to the users game specific data
  static M5GameData& GetGameData(void);
  //Sets the next stage for the game
  static void SetNextStage(M5GameStages nextStage);
  //Tells the game to quit
  static void Quit(void);
  //Tells the stage to restart
  static void Restart(void);

private:
  static void Init(const M5GameData* gameData, int gameDataSize);
  static void Update(void);
  static void Shutdown(void);
  static void ChangeStage(void);

};//end M5StageMgr



#endif //M5_STAGEMGR_H