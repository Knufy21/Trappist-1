#include <Trappist-1\animation\AnimationSheetManager.hpp>

#include <vector>

namespace AnimationSheetManager
{
	std::vector<AnimationSheet> animationSheets(AnimationSheetHandles::COUNT);

	void load(AnimationSheetHandle handle, TextureManager::TextureHandle texHandle, const char *fileName)
	{
		animationSheets[handle].load(texHandle, fileName);
	}

	void load(AnimationSheetHandle handle, TextureManager::TextureHandle texHandle, const std::string &fileName)
	{
		animationSheets[handle].load(texHandle, fileName);
	}

	void unload(AnimationSheetHandle handle)
	{
		//TODO: implement
	}

	AnimationSheet *get(AnimationSheetHandle handle)
	{
		return &animationSheets[handle];
	}
}