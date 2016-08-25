#include "GfxComponent.h"
#include "M5Gfx.h"
#include "M5Mtx44.h"
#include "M5Object.h"
#include "M5IniFile.h"
#include <string>

GfxComponent::GfxComponent(void)
{
	m_pObj = 0;
	m_type = CT_GfxComponent;
	m_textureID = 0;
}
GfxComponent::~GfxComponent(void)
{
	M5Gfx::UnloadTexture(this->m_textureID);
	M5Gfx::UnregisterComponent(this);
}
void GfxComponent::Draw(void) const
{
	M5Mtx44 world;
	world.MakeTransform(m_pObj->scale, 
		m_pObj->rotation, 
		m_pObj->pos, 
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
	pNew->m_pObj = m_pObj;
	pNew->m_type = m_type;
	pNew->m_textureID = m_textureID;

	return pNew;
}
void GfxComponent::SetTextureID(int id)
{
	m_textureID = id;
}
void GfxComponent::FromFile(M5IniFile& iniFile)
{
	std::string path("Textures\\");
	std::string fileName;
	iniFile.SetToSection("GfxComponent");
	iniFile.GetValue("texture", fileName);
	path += fileName;
	m_textureID = M5Gfx::LoadTexture(path.c_str());
}