/******************************************************************************/
/*!
\file   M5Stage.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    2D Game Engine
\date   2016/08/06

Typedefs and struct for M5Stage

*/
/******************************************************************************/
#ifndef M5_STAGE_H
#define M5_STAGE_H

/*!A pointer type for Stage functions */
typedef void(*M5Func)(void);
/*! A pointer type for Stage Update Functions.*/
typedef void(*M5UpdateFunc)(float dt);


/*! A struct to hold the function pointers for a stage.*/
struct M5Stage
{
  M5Func       Load;    /*!< A stages Load function pointer*/
  M5Func       Init;    /*!< A stages Init function pointer*/
  M5UpdateFunc Update;  /*!< A stages update function pointer*/
  M5Func       Shutdown;/*!< A stages Shutdown function pointer*/
  M5Func       Unload;  /*!< A stages unload function pointer*/
};

#endif