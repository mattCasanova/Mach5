/******************************************************************************/
/*!
file    GamePlayStage.cpp
\author Matt Casanova
\\par   email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/09/03

This is a stage for the Mach5 Engine Demo project. This would be a
good place to load game data and initialize object you need for your game.
*/
/******************************************************************************/
#include "GamePlayStage.h"
#include "Core\M5Input.h"
#include "Core\M5StageMgr.h"
#include "Core\M5Object.h"
#include "Core\M5ObjectManager.h"
#include "Core\M5Gfx.h"
#include "Core\GfxComponent.h"



void GamePlayStage::Load(void)
{

}
void GamePlayStage::Init(void)
{
	M5Object* pObj = M5ObjectManager::CreateObject(AT_Player);
	M5Gfx::RegisterWorldComponent(pObj->GetComponent<GfxComponent>(CT_GfxComponent));
}
void GamePlayStage::Update(float /*dt*/)
{
	if (M5Input::IsPressed(M5_ESCAPE))
		M5StageMgr::Quit();
}
void GamePlayStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
void GamePlayStage::Unload(void)
{

}