#pragma once

#include <Trappist-1\graphics\fonts\Character.hpp>
#include <Trappist-1\graphics\fonts\Kerning.hpp>
#include <Trappist-1\graphics\Texture.hpp>

#include <string>
#include <unordered_map>

//namespace
//{
	class Font
	{
	public:
		struct Padding
		{
			int top;
			int left;
			int bottom;
			int right;
		};

		struct Spacing
		{
			int x;
			int y;
		};

		Font();
		~Font();

		// Loads the font with the specified atlas file and the specified font file.
		bool load(const char *atlasFileName, const char *fontFileName);

		// Returns the character info of the ascii character or nullptr if it does not exist.
		const CharacterInfo *getCharacterInfo(unsigned short ascii) const;

		// Returns the kerning info between two characters.
		const KerningInfo *getKerningInfo(unsigned short ascii1, unsigned short ascii2) const;

		// Returns the kerning width amount between two characters.
		float getKerningAmount(unsigned short ascii1, unsigned short ascii2) const;

		// Returns the texture atlas of the font.
		const Texture &getTextureAtlas() const;

		// Returns the padding of the font.
		const Padding &getPadding() const;

		// Returns the spacing of the font.
		const Spacing &getSpacing() const;

		// Returns the line height of the font.
		float getLineHeight() const;

	private:
		unsigned long long ascii_hash(unsigned short ascii1, unsigned short ascii2) const;

		void loadFontFile(const char *fontFileName);
		void readInfo(const std::string &line);
		void readCommon(const std::string &line);
		void readCharacterInfo(const std::string &line);
		void readCharacter(const std::string &line, unsigned int characterIndex);
		void readKerningInfo(const std::string &line);
		void readKerning(const std::string &line, unsigned int kerningIndex);

		Texture textureAtlas;
		std::unordered_map<unsigned short, CharacterInfo> characters;
		std::unordered_map<unsigned long long, KerningInfo> kernings;
		Padding padding;
		Spacing spacing;
		float lineHeight;
		unsigned int size;
	};

	// Inline

	inline unsigned long long Font::ascii_hash(unsigned short ascii1, unsigned short ascii2) const
	{
		return ascii1 * 65536u + ascii2;
	}

	inline const Texture &Font::getTextureAtlas() const
	{
		return this->textureAtlas;
	}

	inline const Font::Padding &Font::getPadding() const
	{
		return this->padding;
	}

	inline const Font::Spacing &Font::getSpacing() const
	{
		return this->spacing;
	}

	inline float Font::getLineHeight() const
	{
		return this->lineHeight;
	}
//}