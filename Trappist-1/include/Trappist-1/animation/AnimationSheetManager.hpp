#pragma once

#include <string>
#include <Trappist-1\animation\AnimationSheet.hpp>
#include <Trappist-1\TextureManager.hpp>

namespace AnimationSheetManager
{
	using AnimationSheetHandle = unsigned char;

	enum AnimationSheetHandles : AnimationSheetHandle
	{
		SHADOW_SLIME,
		COUNT
	};

	// Loads the animation sheet at the specified handle with the specified file name and texture handle.
	void load(AnimationSheetHandle handle, TextureManager::TextureHandle texHandle, const char *fileName);

	// Loads the animation sheet at the specified handle with the specified file name and texture handle.
	void load(AnimationSheetHandle handle, TextureManager::TextureHandle texHandle, const std::string &fileName);

	// Unloads the animation sheet at the specified handle (Frees gpu memory).
	void unload(AnimationSheetHandle handle);

	// Returns the animation sheet at the specified handle.
	AnimationSheet *get(AnimationSheetHandle handle);
}