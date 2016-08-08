/******************************************************************************/
/*!
\file   SplashState.h
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    class:
\par    Assignment:
\date   2012/12/6

This is a stage for the Mach5 Engine Demo project. A Splash stage is a good 
place to load data and/or resources that you will need for all of your stages.
*/
/******************************************************************************/
#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H


void SplashStateLoad(void);
void SplashStateInit(void);
void SplashStateUpdate(float dt);
void SplashStateShutdown(void);
void SplashStateUnload(void);


#endif /* SPLASHSTATE_H */