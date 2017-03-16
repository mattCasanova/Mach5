/******************************************************************************/
/*!
\file   RandomGoStates.cpp
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2017/03/15

All of the States for the RandomGoComponent Statemachine.
*/
/******************************************************************************/
#include "RandomGoStates.h"
#include "RandomGoComponent.h"

#include "Core\M5Random.h"
#include "Core\M5Object.h"
#include "Core\M5Intersect.h"
#include "Core\M5Gfx.h"
#include "Core\M5Math.h"
#include <cmath>

FindState::FindState(RandomGoComponent* parent): m_parent(parent)
{
}
void FindState::Enter()
{
	M5Vec2 botLeft;
	M5Vec2 topRight;
	M5Gfx::GetWorldBotLeft(botLeft);
	M5Gfx::GetWorldTopRight(topRight);

	M5Vec2 target;
	target.x = M5Random::GetFloat(botLeft.x, topRight.x);
	target.y = M5Random::GetFloat(botLeft.y, topRight.y);

	m_parent->SetTarget(target);

}
void FindState::Update(float)
{
	m_parent->SetNextState(m_parent->GetState(RGS_ROTATE_STATE));
}
void FindState::Exit()
{
}


RotateState::RotateState(RandomGoComponent* parent): m_parent(parent)
{
}
void RotateState::Enter()
{
	M5Vec2 target = m_parent->GetTarget();

	M5Vec2::Sub(m_dir, target, m_parent->GetM5Object()->pos);
	
	m_targetRot = std::atan2f(m_dir.y, m_dir.x);
	m_targetRot = M5Math::Wrap(m_targetRot, 0.f, M5Math::TWO_PI);
	
	m_parent->GetM5Object()->rotationVel = m_parent->GetRotationSpeed();
}
void RotateState::Update(float)
{
	m_parent->GetM5Object()->rotation = M5Math::Wrap(m_parent->GetM5Object()->rotation, 0.f, M5Math::TWO_PI);
	
	if (M5Math::IsInRange(m_parent->GetM5Object()->rotation, m_targetRot - .1f, m_targetRot + .1f))
		m_parent->SetNextState(m_parent->GetState(RGS_GO_STATE));
}
void RotateState::Exit()
{
	m_parent->GetM5Object()->rotationVel = 0;
	
	m_dir.Normalize();
	M5Vec2::Scale(m_dir, m_dir, m_parent->GetSpeed());
	
	m_parent->GetM5Object()->vel = m_dir;
}


GoState::GoState(RandomGoComponent* parent): m_parent(parent)
{
}
void GoState::Enter()
{
}
void GoState::Update(float)
{
	M5Vec2 target = m_parent->GetTarget();
	if (M5Intersect::PointCircle(target, m_parent->GetM5Object()->pos, m_parent->GetM5Object()->scale.x))
		m_parent->SetNextState(m_parent->GetState(RGS_FIND_STATE));
}
void GoState::Exit()
{
	m_parent->GetM5Object()->vel.Set(0, 0);
}
