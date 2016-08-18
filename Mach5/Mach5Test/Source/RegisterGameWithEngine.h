/******************************************************************************/ 
/*! 
\file   RegisterGameWithEngine.h 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Stages in the 
current project.  UserPreBuild.bat looks for files of the type *Stage.h 
and registers those stages with the StageMgr. 
*/ 
/******************************************************************************/ 
#ifndef REGISTER_GAME_WITH_ENGINE_H 
#define REGISTER_GAME_WITH_ENGINE_H 
 
#include "M5StageMgr.h" 
#include "M5StageTypes.h" 
#include "M5TemplateBuilder.h" 
#include "Game1Stage.h" 
#include "Game2Stage.h" 
#include "GameOverStage.h" 
#include "SplashStage.h" 
inline void RegisterGameWithEngine(void) {  
 M5StageMgr::AddStage(ST_Game1Stage, new M5TemplateBuilder< Game1Stage >() ); 
 M5StageMgr::AddStage(ST_Game2Stage, new M5TemplateBuilder< Game2Stage >() ); 
 M5StageMgr::AddStage(ST_GameOverStage, new M5TemplateBuilder< GameOverStage >() ); 
 M5StageMgr::AddStage(ST_SplashStage, new M5TemplateBuilder< SplashStage >() ); 
} 
#endif //REGISTER_GAME_WITH_ENGINE_H 
