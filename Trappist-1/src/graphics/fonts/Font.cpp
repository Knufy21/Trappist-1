#include <Trappist-1\graphics\fonts\Font.hpp>

#include <fstream>
#include <sstream>

#define FONT_FILE_VALUE_SPLITTER '='
#define FONT_FILE_NUMBER_SPLITTER ','

//namespace
//{
	Font::Font()
	{  }

	Font::~Font()
	{  }

	bool Font::load(const char *atlasFileName, const char *fontFileName)
	{
		bool result = false;
		textureAtlas.load(atlasFileName);
		textureAtlas.setSmooth(false);
		loadFontFile(fontFileName);

		return result;
	}

	const CharacterInfo *Font::getCharacterInfo(unsigned short ascii) const
	{
		return &(this->characters.at(ascii));
	}

	const KerningInfo *Font::getKerningInfo(unsigned short ascii1, unsigned short ascii2) const
	{
		auto &it = kernings.find(ascii_hash(ascii1, ascii2));
		if (it != kernings.end())
			return &it->second;
		return nullptr;
	}

	float Font::getKerningAmount(unsigned short ascii1, unsigned short ascii2) const
	{
		auto &it = kernings.find(ascii_hash(ascii1, ascii2));
		if (it != kernings.end())
			return it->second.amount;
		return 0.0f;
	}

	void Font::loadFontFile(const char *fontFileName)
	{
		std::ifstream file(fontFileName);
		if (file.bad())
		{
			printf("Couldn't open file '%s'", fontFileName);
			return;
		}
		sizeof(long);
		std::string line;

		// Read first two lines
		std::getline(file, line);
		readInfo(line);
		std::getline(file, line);
		readCommon(line);

		// Skip unnecessary stuff
		std::getline(file, line);
		std::getline(file, line);

		// Read Characters
		readCharacterInfo(line);
		unsigned int index = 0;
		while (std::getline(file, line))
		{
			if (line[0] == 'c')
			{
				readCharacter(line, index);
				++index;
			}
			else break;
		}

		// Read kernings
		readKerningInfo(line);
		index = 0;
		while (std::getline(file, line))
		{
			if (line[0] == 'k')
			{
				readKerning(line, index);
				++index;
			}
			else break;
		}

		file.close();
	}

	void Font::readInfo(const std::string &line)
	{
		std::stringstream ssLine(line);
		std::string item;
		std::string keyValuePair[2];
		while (std::getline(ssLine, item, ' '))
		{
			std::stringstream ssItem(item);
			std::getline(ssItem, keyValuePair[0], FONT_FILE_VALUE_SPLITTER);
			std::getline(ssItem, keyValuePair[1], FONT_FILE_VALUE_SPLITTER);

			if (keyValuePair[0] == "size")
			{
				size = std::stoul(keyValuePair[1]) - 3; // TODO: check why -8
			}
			else if (keyValuePair[0] == "padding")
			{
				std::stringstream ssPadding(keyValuePair[1]);
				std::string padValue;
				std::getline(ssPadding, padValue, FONT_FILE_VALUE_SPLITTER);
				padding.top = std::stoi(padValue);
				std::getline(ssPadding, padValue, FONT_FILE_VALUE_SPLITTER);
				padding.left = std::stoi(padValue);
				std::getline(ssPadding, padValue, FONT_FILE_VALUE_SPLITTER);
				padding.bottom = std::stoi(padValue);
				std::getline(ssPadding, padValue, FONT_FILE_VALUE_SPLITTER);
				padding.right = std::stoi(padValue);
			}
			else if (keyValuePair[0] == "spacing")
			{
				std::stringstream ssSpacing(keyValuePair[1]);
				std::string spacingValue;
				std::getline(ssSpacing, spacingValue, FONT_FILE_VALUE_SPLITTER);
				spacing.x = std::stoi(spacingValue);
				std::getline(ssSpacing, spacingValue, FONT_FILE_VALUE_SPLITTER);
				spacing.y = std::stoi(spacingValue);
			}
		}
	}

	void Font::readCommon(const std::string &line)
	{
		std::stringstream ssLine(line);
		std::string item;
		std::string keyValuePair[2];
		while (std::getline(ssLine, item, ' '))
		{
			std::stringstream ssItem(item);
			std::getline(ssItem, keyValuePair[0], FONT_FILE_VALUE_SPLITTER);
			std::getline(ssItem, keyValuePair[1], FONT_FILE_VALUE_SPLITTER);

			if (keyValuePair[0] == "lineHeight")
			{
				lineHeight = std::stof(keyValuePair[1]) / static_cast<float>(size);
			}
		}
	}

	void Font::readCharacterInfo(const std::string &line)
	{
		std::stringstream ss(line);
		std::string item;
		std::getline(ss, item, FONT_FILE_VALUE_SPLITTER);
		std::getline(ss, item, FONT_FILE_VALUE_SPLITTER);
		this->characters.reserve(std::stoul(item));
	}

	void Font::readCharacter(const std::string &line, unsigned int characterIndex)
	{
		std::stringstream ssLine(line);
		std::string item;
		std::string keyValuePair[2];
		
		CharacterInfo *result = nullptr;
		while (std::getline(ssLine, item, ' '))
		{
			if (item.empty())
				continue;

			std::stringstream ssItem(item);
			std::getline(ssItem, keyValuePair[0], FONT_FILE_VALUE_SPLITTER);
			std::getline(ssItem, keyValuePair[1], FONT_FILE_VALUE_SPLITTER);

			if (keyValuePair[0] == "id") {
				unsigned short idval = static_cast<unsigned short>(std::stoi(keyValuePair[1]));
				result = &characters[idval];
			}
			else if (keyValuePair[0] == "x")
				result->texCoord.x = (std::stof(keyValuePair[1])) / textureAtlas.getSize().x;
			else if (keyValuePair[0] == "y")
				result->texCoord.y = (std::stof(keyValuePair[1])) / textureAtlas.getSize().y;
			else if (keyValuePair[0] == "width") {
				float width = std::stof(keyValuePair[1]);
				result->size.x = width;
				result->texSize.x = (width) / textureAtlas.getSize().x;
				result->size.x /= static_cast<float>(size);
			}
			else if (keyValuePair[0] == "height") {
				float height = std::stof(keyValuePair[1]);
				result->size.y = height;
				result->texSize.y = (height) / textureAtlas.getSize().y;
				result->size.y /= static_cast<float>(size);
			}
			else if (keyValuePair[0] == "xoffset")
				result->offset.x = std::stof(keyValuePair[1]) / static_cast<float>(size);
			else if (keyValuePair[0] == "yoffset")
				result->offset.y = std::stof(keyValuePair[1]) / static_cast<float>(size);
			else if (keyValuePair[0] == "xadvance")
				result->advance = std::stof(keyValuePair[1]) / static_cast<float>(size);
		}
	}

	void Font::readKerningInfo(const std::string &line)
	{
		std::stringstream ss(line);
		std::string item;
		std::getline(ss, item, FONT_FILE_VALUE_SPLITTER);
		std::getline(ss, item, FONT_FILE_VALUE_SPLITTER);
		this->kernings.reserve(std::stoul(item));
	}

	void Font::readKerning(const std::string &line, unsigned int keringIndex)
	{
		std::stringstream ssLine(line);
		std::string item;
		std::string keyValuePair[2];

		unsigned short ascii1 = 0;
		unsigned short ascii2 = 0;
		float amount;

		while (std::getline(ssLine, item, ' '))
		{
			if (item.empty())
				continue;

			std::stringstream ssItem(item);
			std::getline(ssItem, keyValuePair[0], FONT_FILE_VALUE_SPLITTER);
			std::getline(ssItem, keyValuePair[1], FONT_FILE_VALUE_SPLITTER);

			if (keyValuePair[0] == "first")
				ascii1 = static_cast<unsigned short>(std::stoul(keyValuePair[1]));
			else if(keyValuePair[0] == "second")
				ascii2 = static_cast<unsigned short>(std::stoul(keyValuePair[1]));
			else if (keyValuePair[0] == "amount")
				amount = std::stof(keyValuePair[1]) / static_cast<float>(size);
		}

		this->kernings[ascii_hash(ascii1, ascii2)].amount = amount;
	}
//}