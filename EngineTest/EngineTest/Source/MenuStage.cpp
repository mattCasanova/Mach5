/******************************************************************************/
/*!
\file   MainMenuStage.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/17

The MainMenu in AstroShot
*/
/******************************************************************************/
#include "MainMenuStage.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5App.h"
#include "Core\M5IniFile.h"
#include "Core\M5StageManager.h"
#include "Core\M5GameData.h"
#include "SpaceShooterHelp.h"
#include <string>

MainMenuStage::MainMenuStage(void)
{
}
MainMenuStage::~MainMenuStage(void)
{
}
void MainMenuStage::Init(void)
{
	std::string loadDir = "Stages\\";
	//Create ini reader and starting vars
	M5IniFile iniFile;
	//Load file
	iniFile.ReadFile(loadDir + M5StageManager::GetGameData().menuFile);
	//Read Objects From IniFile
	LoadObjects(iniFile);
}
void MainMenuStage::Update(float /*dt*/)
{
}
void MainMenuStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
