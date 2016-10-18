/******************************************************************************/
/*!
\file   ChangeStageCommand.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change stages
*/
/******************************************************************************/
#ifndef CHANGE_STAGE_COMMAND_H
#define CHANGE_STAGE_COMMAND_H

#include "M5Command.h"
#include "M5StageTypes.h"

class ChangeStageCommand : public M5Command
{
public:
	ChangeStageCommand(M5StageTypes nextStage);
	ChangeStageCommand(void);
	void Execute(void);
	void SetNextStage(M5StageTypes nextStage);
	ChangeStageCommand* Clone(void) const;
private:
	M5StageTypes m_stage;
};


#endif //CHANGE_STAGE_COMMAND_H
