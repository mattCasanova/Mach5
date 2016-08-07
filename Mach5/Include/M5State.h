/******************************************************************************/
/*!
\file   M5State.h
\author Matt Casanova
\par    email: mcasanov\@digipen.edu
\par    GAM150
\par    Simple 2D Game Engine
\date   2012/11/26

Typedefs and struct for my M5State

*/
/******************************************************************************/
#ifndef M5_STATE_H
#define M5_STATE_H

/*!A pointer type for State functions */
typedef void(*M5Func)(void);
/*! A pointer type for State Update Functions.*/
typedef void(*M5UpdateFunc)(float dt);


/*! A struct to hold the function pointers for states.*/
struct M5State
{
  M5Func       Load;    /*!< A states Load function pointer*/
  M5Func       Init;    /*!< A states Init function pointer*/
  M5UpdateFunc Update;  /*!< A states update function pointer*/
  M5Func       Shutdown;/*!< A states Shutdown function pointer*/
  M5Func       Unload;  /*!< A states unload function pointer*/
};

#endif