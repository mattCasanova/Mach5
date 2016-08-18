#include "GfxComponent.h"
#include "M5Gfx.h"
#include "M5Mtx44.h"
#include "M5Object.h"

GfxComponent::GfxComponent(void)
{
	m_pParent = 0;
	m_type = CT_GraphicsComponent;
	m_textureID = 0;
	M5Gfx::RegisterComponent(this);

}
GfxComponent::~GfxComponent(void)
{
	M5Gfx::UnregisterComponent(this);
}
void GfxComponent::Draw(void) const
{
	M5Mtx44 world;
	world.MakeTransform(m_pParent->m_scale, 
		m_pParent->m_rotation, 
		m_pParent->m_position, 
		0);
	M5Gfx::SetTexture(m_textureID);
	M5Gfx::Draw(world);
}
void GfxComponent::Update(float /*dt*/)
{
}
M5Component* GfxComponent::Clone(void)
{
	GfxComponent* pNew = new GfxComponent;
	pNew->m_pParent = m_pParent;
	pNew->m_type = m_type;
	pNew->m_textureID = m_textureID;

	return pNew;
}
void GfxComponent::SetTextureID(int id)
{
	m_textureID = id;
}