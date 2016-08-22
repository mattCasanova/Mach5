/******************************************************************************/ 
/*! 
\file   RegisterStages.h 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Stages in the 
current project.  UserPreBuild.bat looks for files named *Stage.h 
and registers those stages with the StageMgr. 
*/ 
/******************************************************************************/ 
#ifndef REGISTER_STAGES_H 
#define REGISTER_STAGES_H 
 
#include "M5StageMgr.h" 
#include "M5StageTypes.h" 
#include "M5StageBuilder.h" 
#include "Game1Stage.h" 
#include "Game2Stage.h" 
#include "GameOverStage.h" 
#include "SplashStage.h" 
 
 
inline void RegisterStages(void) {  
 M5StageMgr::AddStage(ST_Game1Stage, new M5StageTBuilder< Game1Stage >() ); 
 M5StageMgr::AddStage(ST_Game2Stage, new M5StageTBuilder< Game2Stage >() ); 
 M5StageMgr::AddStage(ST_GameOverStage, new M5StageTBuilder< GameOverStage >() ); 
 M5StageMgr::AddStage(ST_SplashStage, new M5StageTBuilder< SplashStage >() ); 
} 
#endif //REGISTER_STAGES_H 
