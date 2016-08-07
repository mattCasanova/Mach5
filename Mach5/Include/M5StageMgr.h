/******************************************************************************/
/*!
\file   M5StageMgr.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Prototypes for the StageMgr functions

*/
/******************************************************************************/
#ifndef M5_STAGEMGR_H
#define M5_STAGEMGR_H

//Forward Declarations
struct M5State;
struct M5GameData;

//! Functions to control the different states of the game.
class M5StageMgr
{
public:
  friend class M5App;

  //Adds a state the the StageMgr
  static int  AddState(const M5State& state);
  //Sets the given state ID to the starting state of the game
  static void SetStartState(int startState);
  //Test if the game is quitting
  static bool IsQuitting(void);
  //Test state is restarting
  static bool IsRestarting(void);
  //Gets the previous state of the game
  static int  GetPreviousState(void);
  //Gets the Current State of the game
  static int  GetCurrentState(void);
  //Gets the Next state of the game
  static int  GetNextState(void);
  //Gets the pointer to the users game specific data
  static M5GameData& GetGameData(void);
  //Sets the next state for the game
  static void SetNextState(int nextState);
  //Tells the game to quit
  static void Quit(void);
  //Tells the state to restart
  static void Restart(void);

private:
  static void Init(const M5GameData* gameData, int gameDataSize);
  static void Update(void);
  static void Shutdown(void);
  static void ChangeState(void);

};//end M5StageMgr



#endif //M5_STAGEMGR_H