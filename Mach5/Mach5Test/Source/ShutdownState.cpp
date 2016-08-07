/******************************************************************************/
/*!
file    GameOverState.cpp
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

The GameOver state is really used just to quit.  Since I have an Splash 
state, I make sure to have an GameOver state even though for the demo I don't 
do anything here.
*/
/******************************************************************************/
#include "GameOverState.h"
#include "WEStateManager.h"

/******************************************************************************/
/*!
The GameOver state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameOverLoad(void)
{
}
/******************************************************************************/
/*!
The GameOver state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.
*/
/******************************************************************************/
void GameOverInit(void)
{
}
/******************************************************************************/
/*!
The GameOver state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverUpdate(float /*dt*/)
{
  WEStateManager::Quit();
}
/******************************************************************************/
/*!
The GameOver state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverShutdown(void)
{
}
/******************************************************************************/
/*!
The GameOver state is really used just to quit.  Since I have an init 
state, I make sure to have an quit state even though for the demo I don't 
do anything here.

*/
/******************************************************************************/
void GameOverUnload(void)
{
}
