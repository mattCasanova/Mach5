/******************************************************************************/
/*!
\file   ChangeStageCommand.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/10/16

Creates a command to change stages
*/
/******************************************************************************/
#include "ChangeStageCommand.h"
#include "M5StageManager.h"


ChangeStageCommand::ChangeStageCommand(M5StageTypes nextStage):m_stage(nextStage)
{
}
ChangeStageCommand::ChangeStageCommand(void) :m_stage(ST_INVALID)
{
}
void ChangeStageCommand::Execute(void)
{
	M5StageManager::SetNextStage(m_stage);
}
ChangeStageCommand* ChangeStageCommand::Clone(void) const
{
	ChangeStageCommand* pClone = new ChangeStageCommand(*this);
	return pClone;
}
void ChangeStageCommand::SetNextStage(M5StageTypes nextStage)
{
	m_stage = nextStage;
}