/******************************************************************************/
/*!
file    GameStage2.c
\author Matt Casanova 
\par    email: mcasanov\@digipen.edu
\par    Class:Game150
\par    Assignment:Simple Game Engine
\date   2012/12/14

*/
/******************************************************************************/
#include "GameState2.h"


#include "M5App.h"
#include "M5DebugTools.h"
#include "M5Math.h"
#include "M5Vec2.h"
#include "M5Mtx44.h"
#include "M5StageMgr.h"
#include "M5Gfx.h"
#include "M5Input.h"
#include "DemoStates.h"

/*Create a struct for shared stage data*/
typedef struct 
{
  int texture2ID;
  int texture3ID;
  int texture4ID;
  float cameraZ;
  float cameraX;
  float cameraY;
  float cameraRot;
  float rotation;
  float textcoord;
  float totalTime;
  float viewTimer;
}GameStage2Data;

/*Create a static variable so it can't be used in other file*/
static GameStage2Data stageData;

/*How long each frame is.*/
#define M5_ANI_TIMER .1f
#define M5_MAX_TIME 5.f

/******************************************************************************/
/*!
Load my textures here

*/
/******************************************************************************/
void GameState2Load(void)
{
  /*Load my textures used for this stage*/
  stageData.texture2ID = M5Gfx::LoadTexture("Textures\\MainChar.tga");
  stageData.texture3ID = M5Gfx::LoadTexture("Textures\\HUD.tga");
  stageData.texture4ID = M5Gfx::LoadTexture("Textures\\BG.tga");

}
/******************************************************************************/
/*!
Initialize some data

*/
/******************************************************************************/
void GameState2Init(void)
{
  /*The initial values for my camera*/
  stageData.cameraZ   = 60.f;
  stageData.cameraX   = 0.f;
  stageData.cameraY   = 0.f;
  stageData.cameraRot = 0.0f;

  stageData.rotation  = 0;
  stageData.textcoord = 0.0f;
  stageData.totalTime = 0.0f;
  /*Set the background color*/
  M5Gfx::SetBackgroundColor(0.0f, 1.0f, 1.0f);

  /*give a time greater than 5 seconds so I don't begin with a 
  small view port.*/
  stageData.viewTimer = M5_MAX_TIME + 1;
}
/******************************************************************************/
/*!
Update game and draw objects

*/
/******************************************************************************/
void GameState2Update(float dt)
{
  M5Mtx44 transform;

  /*Get Corner points in world*/
  M5Vec2 topLeft;
  M5Vec2 botRight;
  M5Vec2 botLeft;
  M5Vec2 mouse;
  M5Vec2 windowSize = M5App::GetResolution();

  M5Gfx::GetWorldTopLeft(topLeft);
  M5Gfx::GetWorldBotRight(botRight);
  M5Gfx::GetWorldBotLeft(botLeft);

#ifdef _DEBUG
  M5Vec2 leftThumb;
  M5Vec2 rightThumb;
  M5Input::GetLeftThumb(leftThumb);
  M5Input::GetRightThumb(rightThumb);
  float leftTrigger = M5Input::GetLeftTrigger();
  float rightTrigger = M5Input::GetRightTrigger();

  M5DEBUG_CLEAR();
  M5DEBUG_PRINT("Left Trigger: %f\n", leftTrigger);
  M5DEBUG_PRINT("RightTrigger: %f\n", rightTrigger);
  M5DEBUG_PRINT("Left  Thumb : x = %f, y = %f\n", leftThumb.x, leftThumb.y);
  M5DEBUG_PRINT("Right Thumb : x = %f, y = %f\n", rightThumb.x, rightThumb.y);
 #endif 
  

  /*Update my counters*/
  stageData.rotation += dt;
  stageData.totalTime += dt;

  /*Check for input*/
  if (M5Input::IsTriggered(M5_N) ||
      M5Input::IsTriggered(M5_GAMEPAD_START))
  {
    M5StageMgr::SetNextStage(DS_GAMEOVER);
  }
  else if(M5Input::IsTriggered(M5_V))
  {
    M5Gfx::SetViewport(
      (int)windowSize.x  /4,
      (int)windowSize.y / 4,
      (int)windowSize.x / 2,
      (int)windowSize.y / 2);
    stageData.viewTimer = 0.f;
  }
  else if(M5Input::IsTriggered(M5_R) || 
          M5Input::IsTriggered(M5_GAMEPAD_BACK))
  {
    M5StageMgr::Restart();
  }

  /*Check for more input*/
  if (M5Input::IsPressed(M5_MOUSE_MIDDLE_UP) || 
      M5Input::IsPressed(M5_GAMEPAD_LEFT_THUMB))
    --stageData.cameraZ;
  else if (M5Input::IsPressed(M5_MOUSE_MIDDLE_DOWN) || 
           M5Input::IsPressed(M5_GAMEPAD_RIGHT_THUMB))
    ++stageData.cameraZ;

  /*Check for more input*/
  if (M5Input::IsPressed(M5_W) || 
      M5Input::IsPressed(M5_GAMEPAD_DPAD_UP))
    ++stageData.cameraY;
  else if(M5Input::IsPressed(M5_S) || 
          M5Input::IsPressed(M5_GAMEPAD_DPAD_DOWN))
    --stageData.cameraY;

  /*Check for more input*/
  if(M5Input::IsPressed(M5_A) || 
     M5Input::IsPressed(M5_GAMEPAD_DPAD_LEFT))
    --stageData.cameraX;
  else if(M5Input::IsPressed(M5_D) || 
          M5Input::IsPressed(M5_GAMEPAD_DPAD_RIGHT))
    ++stageData.cameraX;


  /*Check for camera rotation*/
  if(M5Input::IsPressed(M5_Q) || 
     M5Input::IsPressed(M5_GAMEPAD_LEFT_SHOULDER))
  {
    stageData.cameraRot -= .01f;
    M5Math::Wrap(stageData.cameraRot, 0.0f, M5Math::TWO_PI);
  }
  else if(M5Input::IsPressed(M5_E) || 
          M5Input::IsPressed(M5_GAMEPAD_RIGHT_SHOULDER))
  {
    stageData.cameraRot += .01f;
    M5Math::Wrap(stageData.cameraRot, 0.0f, M5Math::TWO_PI);
  }

  /*Update the camera since it could have moved*/
  M5Gfx::SetCamera(stageData.cameraX, stageData.cameraY, stageData.cameraZ,
    stageData.cameraRot);

  /*Update stage logic*/
  if(stageData.totalTime > M5_ANI_TIMER)
  {
    stageData.totalTime = 0.0f;
    stageData.textcoord += .25f;
    M5Math::Wrap(stageData.textcoord, 0.0f, 1.0f);
  }
 
  if(stageData.viewTimer < M5_MAX_TIME)
  {
    stageData.viewTimer += dt;
    if(stageData.viewTimer > M5_MAX_TIME)
    {
      /*Reset our view port*/
      M5Gfx::SetViewport(0, 0, (int)windowSize.x, (int)windowSize.y);
    }
  }

  /*Start drawing*/
  M5Gfx::StartScene();
  /*Use perspective matrix for world objects with z order*/
  M5Gfx::SetToPerspective();


  /*Draw BackGround*/
  /*Set image information*/
  M5Gfx::SetTexture(stageData.texture4ID);//Background
  M5Gfx::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

  /*Draw an object with a transform and apply a color*/
  M5Gfx::SetTextureColor(0xFFFFFFFF);
  M5Mtx44::MakeTransform(transform, 
    400.f, 
    200.f,
    0.0f,
    0.f,
    0.f, 
    0.0f);
  M5Gfx::Draw(transform);



  /*Draw Bottom Right*/
  /*Draw an object with different transform and different color*/
  M5Gfx::SetTextureColor(255, 0, 0, 255);
  M5Mtx44::MakeTransform(transform, 15.0f, 25.0f,
    -stageData.rotation / 3,
    botRight.x, 
    botRight.y, 1.0f);
  M5Gfx::Draw(transform);



  /*Draw Top left*/
  /*Another object*/
  M5Gfx::SetTextureColor(0xFFFF0000);
  M5Mtx44::MakeTransform(transform, 25.0f, 10.0f,
    stageData.rotation * 2,
    topLeft.x, 
    topLeft.y, 1.0f);
  M5Gfx::Draw(transform);



  /*Draw bottom left*/
  /*Another object*/
  M5Gfx::SetTextureColor(0x55FFFFFF);
  M5Mtx44::MakeTransform(transform, 10.0f, 10.0f,
    stageData.rotation,
    botLeft.x,
    botLeft.y, 1.0f); 
  M5Gfx::Draw(transform);
  


  /*Draw main character*/
  /*Set image information for main character*/
  M5Gfx::SetTexture(stageData.texture2ID);//Main Character
  M5Gfx::SetTextureColor(0xFFFFFFFF);
  /*Change texture coordinates over time*/
  M5Gfx::SetTextureCoords(.25f, 1.0f, 0.0f, stageData.textcoord, 0.0f);

  /*Draw main character at mouse*/
  M5Input::GetMouse(mouse);
  M5Gfx::ConvertScreenToWorld(mouse.x, mouse.y);
  
  M5Mtx44::MakeTransform(transform, 20.0f, 20.0f,
    0.0f,
    mouse.x, mouse.y, 0.0f);
  M5Gfx::Draw(transform);



  /*Draw the HUD*/
  /*Set to orthographic mode.  Camera distance has no effect,
  objects are drawn in screen space*/
  M5Gfx::SetToOrtho();
  M5Gfx::SetTexture(stageData.texture3ID);//HUD
  M5Gfx::SetTextureCoords(1.0f, 1.0f, 0.0f, 0.0f, 0.0f);

  /*Draw an object with a transform and apply a color*/
  M5Mtx44::MakeTransform(transform, 200.f, 100.f,
    0.0f,
    windowSize.x - 100.f,
    windowSize.y - 50 , 0.0f);
  M5Gfx::Draw(transform);



  /*Reset color*/
  M5Gfx::SetTextureColor(0xFFFFFFFF);
/*Draw my text*/
  M5Gfx::WriteText("V: Toggle ViewPort", 640.f, 15.0f);
  M5Gfx::WriteText("N: Continue", 640.f, 0.0f);
  M5Gfx::WriteText("WASD: Move Camera", 640.f, 700.f);
  M5Gfx::WriteText("Mouse Wheel: Zoom", 640.f, 680.f);
  M5Gfx::WriteText("Q/E: Rotate Camera", 640.f, 640.f);

  M5Gfx::EndScene();
}
/******************************************************************************/
/*!
Nothing to do here

*/
/******************************************************************************/
void GameState2Shutdown(void)
{
}
/******************************************************************************/
/*!
Unload my textures

\param pGameData
A pointer to the shared gameData.
*/
/******************************************************************************/
void GameState2Unload(void)
{
  /*Make sure to unload all textures*/
  M5Gfx::UnloadTexture(stageData.texture2ID);
  M5Gfx::UnloadTexture(stageData.texture3ID);
  M5Gfx::UnloadTexture(stageData.texture4ID);

}