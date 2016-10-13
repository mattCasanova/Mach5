/******************************************************************************/ 
/*! 
\file   RegisterArcheTypes.cpp 
\author PreBuild.bat 
\par    email: lazersquad\@gmail.com 
\par    Mach5 Game Engine 
 
This file gets auto generated based on the names of the ArcheTypes in the 
ArcheTypes Folder  UserPreBuild.bat looks for files named *.ini 
and registers those with the ObjectManager. 
*/ 
/******************************************************************************/ 
#include "Core\M5ArcheTypes.h" 
#include "Core\M5ObjectManager.h" 
 
 
void RegisterArcheTypes(void) {  
M5ObjectManager::AddArcheType(AT_Bullet, "ArcheTypes\\Bullet.ini"); 
M5ObjectManager::AddArcheType(AT_Player, "ArcheTypes\\Player.ini"); 
M5ObjectManager::AddArcheType(AT_Raider, "ArcheTypes\\Raider.ini"); 
M5ObjectManager::AddArcheType(AT_Splash, "ArcheTypes\\Splash.ini"); 
M5ObjectManager::AddArcheType(AT_Ufo, "ArcheTypes\\Ufo.ini"); 
} 
