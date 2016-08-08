/******************************************************************************/
/*!
\file   GameOverState.h
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6
 
This is a stage for the Mach5 Engine Demo project. This is a good place to 
release resources for anything that was allocated in SplashState. He we just 
quit the game.
*/
/******************************************************************************/
#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H


void GameOverLoad(void);
void GameOverInit(void);
void GameOverUpdate(float dt);
void GameOverShutdown(void);
void GameOverUnload(void);


#endif /* GAMEOVERSTATE_H */