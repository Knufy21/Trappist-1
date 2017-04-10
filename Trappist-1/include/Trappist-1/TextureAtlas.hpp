#pragma once

#include <string>
#include <unordered_map>

#include <Trappist-1\graphics\Rect.hpp>
#include <Trappist-1\graphics\Texture.hpp>

class TextureAtlas
{
public:
	TextureAtlas();

	// Loads the texture altas with the specified file name without extension and returns true if it has been successful.
	bool load(const char *fileName);

	bool load2(const char *fileName);

	// Unloads the texture and clears the texCoords.
	void unload();

	// Returns the texture of the atlas.
	const Texture *getTexture() const;

	// Returns the texture coords of the with name specified texture part.
	const FloatRect &getTexCoord(const std::string &name) const;

	// Returns the smooth property of the texture.
	bool isSmooth() const;

	// Sets the smooth property of the texture.
	void setSmooth(bool smooth);

private:
	Texture texture;
	std::unordered_map<std::string, FloatRect> texCoords;
};

// Inline

inline const Texture *TextureAtlas::getTexture() const
{
	return &this->texture;
}

inline const FloatRect &TextureAtlas::getTexCoord(const std::string &name) const
{
	return texCoords.find(name)->second;
}

inline bool TextureAtlas::isSmooth() const
{
	return texture.isSmooth();
}

inline void TextureAtlas::setSmooth(bool smooth)
{
	texture.setSmooth(smooth);
}