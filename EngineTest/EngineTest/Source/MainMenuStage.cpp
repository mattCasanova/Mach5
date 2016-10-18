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
#include "Core\M5GameData.h"
#include "Core\M5Input.h"
#include "Core\M5StageManager.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5App.h"
#include "Core\M5IniFile.h"
#include "Core\M5Phy.h"
#include "Core\UIButtonComponent.h"
#include "Core\ChangeStageCommand.h"
#include "Core\GfxComponent.h"
#include "SpaceShooterHelp.h"

#include <sstream>
#include <iomanip>

MainMenuStage::MainMenuStage(void)
{
	
}
MainMenuStage::~MainMenuStage(void)
{
}
void MainMenuStage::Init(void)
{
	M5Vec2 windowSize = M5App::GetResolution();

	UIButtonComponent* pButton;
	GfxComponent* pGfx;
	M5Object* pObj = M5ObjectManager::CreateObject(AT_UIButton);
	pObj->pos.Set(windowSize.x/2, windowSize.y * .5f);
	pObj->scale.Set(256, 64);
	pObj->GetComponent(CT_UIButtonComponent, pButton);
	pButton->SetOnClick(new ChangeStageCommand(ST_GamePlayStage));
	pObj->GetComponent(CT_GfxComponent, pGfx);
	pGfx->SetTexture("Textures//playButton.tga");

	pObj = M5ObjectManager::CreateObject(AT_MenuTitle);
	pObj->pos.Set(windowSize.x / 2, windowSize.y * .75f);

	M5ObjectManager::CreateObject(AT_MenuSpawner);
}
void MainMenuStage::Update(float /*dt*/)
{

}
void MainMenuStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
