#pragma once

#include <string>

namespace TexturePacker
{
	static constexpr const wchar_t *TEXTURE_ATLAS_INFO_FILE_EXTENSION = L".tai";

	bool packFolder(const char *srcFolder, const char *dstFolder, const char *nameWithoutExtension, unsigned int width, unsigned int height, bool hasInfoFile = true);

	// Packs the images in the specified source directory into a png file named fileName (without extension) and creates an info file.
	bool packDirectory(const std::string &sourceDirectory, const std::string &fileName, unsigned int width, unsigned int height);
};