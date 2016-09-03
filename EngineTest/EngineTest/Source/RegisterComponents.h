/******************************************************************************/ 
/*! 
\file   RegisterComponents.h 
\author UserPreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the Components in the 
Include folder and current project.  UserPreBuild.bat looks for files named *Component.h 
and registers those with the ObjectManager. 
*/ 
/******************************************************************************/ 
#ifndef REGISTER_COMPONENTS_H 
#define REGISTER_COMPONENTS_H 
 
#include "Core\M5ObjectManager.h" 
#include "Core\M5ComponentTypes.h" 
#include "Core\M5ComponentBuilder.h" 
#include "Core\GfxComponent.h" 
#include "PlayerInputComponent.h" 
 
 
inline void RegisterComponents(void) {  
 M5ObjectManager::AddComponent(CT_GfxComponent, new M5ComponentTBuilder< GfxComponent >() ); 
 M5ObjectManager::AddComponent(CT_PlayerInputComponent, new M5ComponentTBuilder< PlayerInputComponent >() ); 
} 
#endif //REGISTER_COMPONENTS_H 
