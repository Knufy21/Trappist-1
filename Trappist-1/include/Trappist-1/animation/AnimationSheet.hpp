#pragma once

#include <string>
#include <unordered_map>
#include <glm\glm.hpp>
#include <Trappist-1\graphics\Rect.hpp>
#include <Trappist-1\animation\Animation.hpp>
#include <Trappist-1\graphics\Texture.hpp>
#include <Trappist-1\TextureManager.hpp>

class AnimationSheet
{
public:
	static constexpr const char *ANIMATION_SHEET_INFO_FILE_EXTENSION = (".asi");

	// Loads the animation sheet info file with the specified file name with extension.
	bool load(TextureManager::TextureHandle handle, const std::string &fileName);

	// Returns the animation by name.
	const Animation *getAnimationByName(const std::string &animationName) const;

	// Returns the animation sheet texture.
	const Texture *getTexture() const;

	// Returns the texture rect of the frame associated with the specified state.
	FloatRect getTextureRectByState(Animation::state_t state) const;

private:
	TextureManager::TextureHandle textureHandle;
	std::unordered_map<std::string, Animation> animations;
	glm::ivec2 frameSize;
};

inline const Texture *AnimationSheet::getTexture() const
{
	return TextureManager::get(textureHandle)->getTexture();
}