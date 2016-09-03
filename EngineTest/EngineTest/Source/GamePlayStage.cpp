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
#include "Core\WrapComponent.h"
#include "Core\ClampComponent.h"

#include <vector>

std::vector<M5Object*> player;

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
	player.clear();
	M5ObjectManager::GetAllObjects(AT_Player, player);

	if (M5Input::IsPressed(M5_ESCAPE))
		M5StageMgr::Quit();
	else if(player.size() == 0)
		M5StageMgr::Quit();
	else if (M5Input::IsTriggered(M5_Z))//Dynamically Wrap Object
	{
		//TODO add getObjectsbytype to objectmanager
		M5Component* pComp = player[0]->GetComponent<WrapComponent>(CT_WrapComponent);
		if (pComp != 0)
		{
			player[0]->RemoveComponent(pComp);
			player[0]->AddComponent(new ClampComponent);
		}
	}
	else if (M5Input::IsTriggered(M5_X))//Dynamically Clamp Object
	{
		//TODO add getObjectsbytype to objectmanager
		M5Component* pComp = player[0]->GetComponent<ClampComponent>(CT_ClampComponent);
		if (pComp != 0)
		{
			player[0]->RemoveComponent(pComp);
			player[0]->AddComponent(new WrapComponent);
		}
	}
}
void GamePlayStage::Shutdown(void)
{
	M5ObjectManager::DestroyAllObjects();
}
void GamePlayStage::Unload(void)
{

}