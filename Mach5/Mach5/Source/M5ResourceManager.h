/******************************************************************************/
/*!
\file   M5Gfx.h
\author Matt Casanova
\par    email: lazersquad\@gmail.com
\par    Mach5 Game Engine
\date   2016/08/8

Singleton class to draw and modify the view of the screen
*/
/******************************************************************************/
#ifndef M5RESOURCE_MANAGER_H
#define M5RESOURCE_MANAGER_H

#include <string>
#include <unordered_map>


/*! Enum to contain my different Grx Resources, For now it is just textures
but I will put shaders and meshes here too. */
enum M5ResourceType
{
	RT_TEXTURE
};


class M5ResourceManager
{
public:
	~M5ResourceManager(void);

	int LoadResource(const char* fileName, M5ResourceType type);
	void UnloadResource(int id, M5ResourceType type);

private:
	/*A struct to hold loaded textures*/
	struct M5LoadedTexture
	{
		M5LoadedTexture(const std::string& str, int newID);
		std::string fileName;
		int id;
		int count;
	};

	//Typedef Container to hold loaded textures
	typedef std::unordered_map<const char*, M5LoadedTexture> M5TextureMap;
	typedef M5TextureMap::iterator M5TextureMapItor;


	M5TextureMap s_TextureMap;
};


#endif //M5RESOURCE_MANAGER_H