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
struct M5Stage;

class M5StageBuilder
{
public:
  ~M5StageBuilder() {} //enpty virtual destructor
  virtual M5Stage* Build(void) = 0;
private:
};




#endif // !M5STAGE_BUILDER_H
