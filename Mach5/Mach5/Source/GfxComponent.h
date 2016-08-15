#ifndef GRAPHICS_COMPONENT
#define GRAPHICS_COMPONENT

#include "M5Component.h"

class GraphicsComponent : public M5Component
{
public:
	GraphicsComponent(void);
	~GraphicsComponent(void);
	void Draw(void) const;
	virtual void Update(float dt);
	virtual M5Component* Clone(void);
	void SetTextureID(int id);
private:
	int m_textureID;

};

#endif // !GRAPHICS_COMPONENT

