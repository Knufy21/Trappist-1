#include <Trappist-1\TextureManager.hpp>

#include <vector>

namespace TextureManager
{
	std::vector<TextureAtlas> textures(TextureHandles::COUNT);

	void load(TextureHandle handle, const char *path)
	{
		textures[handle].load(path);
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