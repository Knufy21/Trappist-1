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

bool TextureAtlas::load2(const char *fileName)
{
	if (texCoords.size() > 0)
		unload();

	std::string sourceFile(fileName);

	// Load texture
	texture.load(std::string(sourceFile + ".png").c_str());

	// Load info file
	std::ifstream file(sourceFile + ".tai", std::ios::in | std::ios::binary);

	if (!file.good())
		return false;

	// Read .tai version
	std::int8_t taiVersion = 0;
	file.read(reinterpret_cast<char *>(&taiVersion), sizeof(taiVersion));

	// Write files count
	std::size_t fileCount = 0;
	file.read(reinterpret_cast<char *>(&fileCount), sizeof(fileCount));

	while (fileCount > 0)
	{
		sf::FloatRect rect;
		file.read(reinterpret_cast<char *>(&rect), sizeof(rect));

		std::size_t len;
		file.read(reinterpret_cast<char *>(&len), sizeof(len));

		std::string name;
		name.resize(len);
		file.read(reinterpret_cast<char *>(&name[0]), len * sizeof(*name.c_str()));

		texCoords[name] = rect;

		--fileCount;
	}

	file.close();
	return true;
}

void TextureAtlas::unload()
{
	texture.unload();
	texCoords.clear();
}