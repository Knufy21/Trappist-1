#include <Trappist-1\TextureManager.hpp>

#include <vector>

namespace TextureManager
{
	std::vector<TextureAtlas> textures(TextureHandles::COUNT);

	void load(TextureHandle handle, const char *fileName)
	{
		textures[handle].load2(fileName);
	}

	void load(TextureHandle handle, const std::string &fileName)
	{
		textures[handle].load2(fileName.c_str());
	}

	void unload(TextureHandle handle)
	{
		textures[handle].unload();
	}

	TextureAtlas *get(TextureHandle handle)
	{
		return &textures[handle];
	}
}