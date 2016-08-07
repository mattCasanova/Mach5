/******************************************************************************/
/*!
\file   M5Graphics.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

This file contains the prototypes for the Graphics Functions.

*/
/******************************************************************************/
#ifndef M5_GRAPHICS_H
#define M5_GRAPHICS_H

#include "M5Vec2.h"
#include "M5Mtx44.h"


//! Functions to help draw things in the game.
namespace M5Graphics
{
/*This should be called once before drawing all objects*/
void StartDraw(void);
/*This should be called once after drawing all objects*/
void EndDraw(void);
/*Use this to load a texture from file. Use the return value to draw, 
change texture coords and finally unload the texture*/
int  LoadTexture(const char* fileName);
/*You must unload every texture that you load*/
void UnloadTexture(int textureID);
/*Use this to select the texture that you want to draw*/
void SetTexture(int textureID);
/*This is used to scale, rotate, or translate a texture.
It is bested used for frame animation*/
void SetTextureCoords(float scaleX, float scaleY, float radians,
  float transX, float transY);
/*Sets the position of the camera in perspective mode.  There
is no camera in ortho mode.*/
void SetCamera(float cameraX, float cameraY, float cameraZ,
  float cameraRot);
/*Use this to draw game objects.  Z order and distance from the 
camera effect that size*/
void SetToPerspective(void);
/*Use this to draw HUD objects.  Distance from the camara doesn't 
effect the object*/
void SetToOrtho(void);
/*Draws the selected texture based on the matrix*/
void Draw(const M5Mtx44& worldMatrix);
/*Writes text on the screen*/
void WriteText(const char* text, float x, float y);
/*Changes the background color*/
void SetBackgroundColor(float red, float green, float blue);
/*Blends the given color with the texture*/
void SetTextureColor(unsigned color);
/*Blends the given color with the texture*/
void SetTextureColor(unsigned char red, unsigned char green,
  unsigned char blue, unsigned char alpha);
/*Converts a point in screen space (mouse click) to the correct
position in the world*/
void ConvertScreenToWorld(float& x, float& y);
/*Converts a position in the world into screen space*/
void ConvertWorldToScreen(float& x, float& y);
/*Set where on the the window to draw*/
void SetViewport(int xStart, int yStart, int width, int height);
/*Gets the Top Left corner of the world*/
void GetWorldTopLeft(M5Vec2& outParam);
/*Gets the Top right corner of the world*/
void GetWorldTopRight(M5Vec2& outParam);
/*Gets the Bottom left corner of the world*/
void GetWorldBotLeft(M5Vec2& outParam);
/*Gets the Bottom Right corner of the world*/
void GetWorldBotRight(M5Vec2& outParam);
}//end namespace M5Graphics




#endif