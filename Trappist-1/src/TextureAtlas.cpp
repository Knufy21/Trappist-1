#include <Trappist-1\TextureAtlas.hpp>

#include <fstream>
#include <sstream>

TextureAtlas::TextureAtlas()
{	}

bool TextureAtlas::load(const char *fileName)
{
	if (texCoords.size() > 0)
		unload();

	std::string srcFile(fileName);

	// Load texture
	texture.load(std::string(srcFile + ".png").c_str());

	// Load info file
	std::ifstream file;
	file.open(srcFile + ".txt");

	if (!file.good())
		return false;

	std::string line;
	std::stringstream ss;
	while (std::getline(file, line))
	{
		ss = std::stringstream(line);
		std::getline(ss, line, ' ');
		auto &texCoord = texCoords[line];
		std::getline(ss, line, ' ');
		texCoord.left = std::stof(line);
		std::getline(ss, line, ' ');
		texCoord.top = std::stof(line);
		std::getline(ss, line, ' ');
		texCoord.width = std::stof(line);
		std::getline(ss, line, ' ');
		texCoord.height = std::stof(line);
	}

	file.close();
	return true;
}

void TextureAtlas::unload()
{
	texture.unload();
	texCoords.clear();
}