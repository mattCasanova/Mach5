/******************************************************************************/
/*!
\file   M5Stage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    2D Game Engine
\date   2016/08/08

Base class for M5Stage

*/
/******************************************************************************/
#ifndef M5_STAGE_H
#define M5_STAGE_H


/*! A struct to hold the function pointers for a stage.*/
struct M5Stage
{
public:
  virtual ~M5Stage(void) {}//emtpy virtual destructor
  virtual void Load(void)       = 0;
  virtual void Init(void)       = 0; 
  virtual void Update(float dt) = 0;
  virtual void Shutdown(void)   = 0;
  virtual void Unload(void)     = 0;
};

#endif