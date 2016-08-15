#include "GraphicsComponent.h"
#include "M5Gfx.h"
#include "M5Mtx44.h"
#include "M5GameObject.h"

GraphicsComponent::GraphicsComponent(void)
{
	m_pParent = 0;
	m_type = CT_GraphicsComponent;
	m_textureID = 0;
	M5Gfx::RegisterComponent(this);

}
GraphicsComponent::~GraphicsComponent(void)
{
	M5Gfx::UnregisterComponent(this);
}
void GraphicsComponent::Draw(void) const
{
	M5Mtx44 world;
	world.MakeTransform(m_pParent->m_scale, 
		m_pParent->m_rotation, 
		m_pParent->m_position, 
		0);
	M5Gfx::SetTexture(m_textureID);
	M5Gfx::Draw(world);
}
void GraphicsComponent::Update(float /*dt*/)
{
}
M5Component* GraphicsComponent::Clone(void)
{
	GraphicsComponent* pNew = new GraphicsComponent;
	pNew->m_pParent = m_pParent;
	pNew->m_type = m_type;
	pNew->m_textureID = m_textureID;

	return pNew;
}
void GraphicsComponent::SetTextureID(int id)
{
	m_textureID = id;
}