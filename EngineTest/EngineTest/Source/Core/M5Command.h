/******************************************************************************/
/*!
\file   M5Command.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Interface for Command Design Pattern
*/
/******************************************************************************/
#ifndef M5COMMAND_H
#define M5COMMAND_H

class M5Command
{
public:
	virtual ~M5Command(void) {}//Empty Virtual Destructor
	virtual void Execute(void) = 0;
	virtual M5Command* Clone(void) const = 0;
};


#endif //M5COMMAND_H