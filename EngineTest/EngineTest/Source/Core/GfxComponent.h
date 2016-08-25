#ifndef GFX_COMPONENT
#define GFX_COMPONENT

#include "M5Component.h"

class GfxComponent : public M5Component
{
public:
	GfxComponent(void);
	~GfxComponent(void);
	void Draw(void) const;
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
	virtual void FromFile(M5IniFile& iniFile);
	void SetTextureID(int id);
private:
	int m_textureID;

};

#endif // !GFX_COMPONENT

