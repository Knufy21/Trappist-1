#include <Trappist-1\util\TexturePacker.hpp>

#include <fstream>
#include <vector>
#include <filesystem>

#include <SFML\Graphics\Image.hpp>

#include <Trappist-1\graphics\Rect.hpp>

namespace std
{
	namespace filesystem = experimental::filesystem;
}

namespace TexturePacker
{
	bool packFolder(const char *srcFolder, const char *dstFolder, const char *nameWithoutExtension, unsigned int width, unsigned int height, bool hasInfoFile)
	{
		std::vector<std::string> files;
		if (hasInfoFile)
		{

		}
		else
		{
			std::filesystem::path srcPath(srcFolder);
			std::filesystem::directory_iterator dit(srcPath);
			for (auto &it : std::experimental::filesystem::directory_iterator(srcFolder))
			{
				if (it.path().has_filename() && it.path().extension().string() == (".png"))
				{
					files.push_back(it.path().stem().string());
				}
			}
		}

		std::ifstream file;

		std::string srcFile;
		srcFile.append(srcFolder);
		srcFile.append("/_info.txt");

		file.open(srcFile);
		if (!file.good())
			return false;

		std::string line;

		unsigned int textureCount;
		std::getline(file, line);
		textureCount = std::stoul(line);

		std::vector<sf::Image> images;
		std::vector<std::string> names;
		images.resize(textureCount);
		names.resize(textureCount);

		std::string srcFolderSlash(srcFolder);
		srcFolderSlash += '/';

		unsigned int fieldWidth = 0;
		unsigned int fieldHeight = 0;

		unsigned int index = 0;
		while (textureCount > 0)
		{
			--textureCount;

			std::getline(file, line);
			images[index].loadFromFile(srcFolderSlash + line + ".png");
			names[index] = line;

			if (images[index].getSize().x > fieldWidth)
				fieldWidth = images[index].getSize().x;

			if (images[index].getSize().y > fieldHeight)
				fieldHeight = images[index].getSize().y;

			++index;
		}

		file.close();

		// If field size is greater than texture, make it fit
		if (fieldWidth > width)
			width = fieldWidth;
		if (fieldHeight > height)
			height = fieldHeight;

		sf::Image result;
		result.create(width, height, sf::Color::Transparent);

		// output info file
		std::string dstFile;
		dstFile.append(dstFolder);
		dstFile += '/';
		dstFile.append(nameWithoutExtension);

		std::ofstream ofile;
		ofile.open(dstFile + ".txt");
		if (!ofile.good())
			return false;

		unsigned int top = 0, left = 0;
		std::string textureInfo;
		for (size_t i = 0; i < images.size(); ++i)
		{
			sf::Image &img = images[i];

			// current x, y are valid

			// copy image
			for (unsigned int y = 0; y < img.getSize().y; ++y)
			{
				for (unsigned int x = 0; x < img.getSize().x; ++x)
				{
					result.setPixel(left + x, top + y, img.getPixel(x, y));
				}
			}

			// write info file
			textureInfo.clear();
			textureInfo.append(names[i]);
			textureInfo += ' ';
			textureInfo.append(std::to_string(static_cast<float>(left) / static_cast<float>(width)));
			textureInfo += ' ';
			textureInfo.append(std::to_string(static_cast<float>(top) / static_cast<float>(height)));
			textureInfo += ' ';
			textureInfo.append(std::to_string(static_cast<float>(img.getSize().x) / static_cast<float>(width)));
			textureInfo += ' ';
			textureInfo.append(std::to_string(static_cast<float>(img.getSize().y) / static_cast<float>(height)));
			textureInfo += '\n';

			ofile.write(textureInfo.c_str(), textureInfo.size());

			left += fieldWidth;

			// wrap if next field is out of range
			if (left + fieldWidth > width)
			{
				left = 0;
				top += fieldHeight;
			}
		}

		result.saveToFile(dstFile + ".png");

		ofile.close();

		return true;
	}

	bool packDirectory(const std::string &sourceDirectory, const std::string &fileName, unsigned int width, unsigned int height)
	{
		std::experimental::filesystem::path sourceDirectoryPath(sourceDirectory);
		std::experimental::filesystem::path filePath(fileName);

		std::vector<std::experimental::filesystem::path> files;

		for (auto &file : std::experimental::filesystem::directory_iterator(sourceDirectoryPath))
		{
			if (file.path().has_extension() && !file.path().extension().compare(L".png"))
			{
				files.push_back(file.path().stem());
			}
		}

		std::ofstream outputFile(filePath.replace_extension(L".tai"), std::ios::out | std::ios::binary);
		if (!outputFile.good())
			return false;

		// Write .tai version
		std::int8_t taiVersion = 2;
		outputFile.write((char *)&taiVersion, sizeof(taiVersion));

		// Write files count
		std::size_t fileCount = files.size();
		outputFile.write(reinterpret_cast<const char *>(&fileCount), sizeof(fileCount));

		std::vector<sf::Image> images;
		images.resize(files.size());

		unsigned int fieldWidth = 0;
		unsigned int fieldHeight = 0;

		unsigned int index = 0;
		while (index < files.size())
		{
			std::experimental::filesystem::path sourceDirectoryPathCopy(sourceDirectoryPath);
			std::string s(sourceDirectoryPathCopy.append(files[index].string().append(".png")).string());
			images[index].loadFromFile(s);

			if (images[index].getSize().x > fieldWidth)
				fieldWidth = images[index].getSize().x;

			if (images[index].getSize().y > fieldHeight)
				fieldHeight = images[index].getSize().y;

			++index;
		}

		// If field size is greater than texture, make it fit
		if (fieldWidth > width)
			width = fieldWidth;
		if (fieldHeight > height)
			height = fieldHeight;

		sf::Image result;
		result.create(width, height, sf::Color::Transparent);

		// output info file
		unsigned int top = 0, left = 0;
		for (size_t i = 0; i < images.size(); ++i)
		{
			sf::Image &img = images[i];

			// current x, y are valid

			// copy image
			for (unsigned int y = 0; y < img.getSize().y; ++y)
			{
				for (unsigned int x = 0; x < img.getSize().x; ++x)
				{
					result.setPixel(left + x, top + y, img.getPixel(x, y));
				}
			}
			

			// Write rect values
			FloatRect rect
			{
				static_cast<float>(left) / static_cast<float>(width),
				static_cast<float>(top) / static_cast<float>(height),
				static_cast<float>(img.getSize().x) / static_cast<float>(width),
				static_cast<float>(img.getSize().y) / static_cast<float>(height)
			};
			outputFile.write(reinterpret_cast<const char *>(&rect), sizeof(rect));

			// Write name lenght
			std::size_t len = files[i].string().size();
			outputFile.write(reinterpret_cast<const char *>(&len), sizeof(len));

			// Write name
			outputFile.write(reinterpret_cast<const char *>(files[i].string().c_str()), len * sizeof(*files[i].string().c_str()));

			left += fieldWidth;

			// wrap if next field is out of range
			if (left + fieldWidth > width)
			{
				left = 0;
				top += fieldHeight;
			}
		}

		result.saveToFile(fileName + ".png");

		outputFile.close();

		return true;
	}
}