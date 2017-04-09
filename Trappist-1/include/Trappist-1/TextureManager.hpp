#pragma once

#include <string>
#include <Trappist-1\TextureAtlas.hpp>

namespace TextureManager
{
	using TextureHandle = unsigned char;

	enum TextureHandles : TextureHandle
	{
		TILE_ATLAS,
		TRAPPIST_1_SYSTEM_ATLAS,
		ANIMATION_SHEET_SHADOW_SLIME,
		ANIMATION_SHEET_PLAYER,
		COUNT
	};

	// Loads the texture at the specified handle with the specified file name.
	void load(TextureHandle handle, const char *fileName);

	// Loads the texture at the specified handle with the specified file name.
	void load(TextureHandle handle, const std::string &fileName);

	// Unloads the texture at the specified handle (Frees gpu memory).
	void unload(TextureHandle handle);

	// Returns the texture at the specified handle.
	TextureAtlas *get(TextureHandle handle);
};