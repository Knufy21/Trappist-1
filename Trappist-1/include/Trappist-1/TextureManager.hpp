#pragma once

#include <Trappist-1\TextureAtlas.hpp>

namespace TextureManager
{
	using TextureHandle = unsigned char;

	enum TextureHandles : TextureHandle
	{
		TILE_ATLAS,

		COUNT
	};

	// Loads the texture at the specified handle with the specified path.
	void load(TextureHandle handle, const char *path);

	// Unloads the texture at the specified handle (Frees gpu memory).
	void unload(TextureHandle handle);

	// Returns the texture at the specified handle.
	TextureAtlas *get(TextureHandle handle);
};