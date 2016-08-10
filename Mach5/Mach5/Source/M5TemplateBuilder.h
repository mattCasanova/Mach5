/******************************************************************************/
/*!
\file   M5TemplateBuilder.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/10

Template class Builder for easily instantiating Game Stages

*/
/******************************************************************************/
#ifndef M5TEMPLATE_BUILDER_H
#define M5TEMPLATE_BUILDER_H

#include "M5StageBuilder.h"

template <typename T>
class M5TemplateBuilder : public M5StageBuilder
{
public:
  virtual M5Stage* Build(void);
private:
};


template <typename T> 
M5Stage* M5TemplateBuilder<T>::Build(void)
{
  return new T();
}



#endif // !M5TEMPLATE_BUILDER_H
