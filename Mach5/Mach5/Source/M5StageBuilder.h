/******************************************************************************/
/*!
\file   M5StageBuilder.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

Base class Builder for easily instantiating Game Stages

*/
/******************************************************************************/
#ifndef M5STAGE_BUILDER_H
#define M5STAGE_BUILDER_H

//Forward declaration
class M5Stage;

//! Base Builder class to create Game Stages via a StageFactory
class M5StageBuilder
{
public:
  ~M5StageBuilder() {} //empty virtual destructor
  //! Virtual Build call that must be overloaded by all Derived Builders
  virtual M5Stage* Build(void) = 0;
private:
};




#endif // !M5STAGE_BUILDER_H
