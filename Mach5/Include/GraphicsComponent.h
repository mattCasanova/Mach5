#ifndef GRAPHICS_COMPONENT
#define GRAPHICS_COMPONENT

#include "M5Component.h"

class GfxComponent : public M5Component
{
public:
	GfxComponent(void);
	~GfxComponent(void);
	void Draw(void) const;
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
	void SetTextureID(int id);
private:
	int m_textureID;

};

#endif // !GRAPHICS_COMPONENT

