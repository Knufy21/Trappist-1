#include <Trappist-1\World.hpp>
#include <Trappist-1\entities\Entity.hpp>

#include <SFML\Graphics\Image.hpp>

#include <fstream>

namespace World
{
	std::vector<Entity*>::iterator iterator;
	std::vector<Entity*> entities;

	std::vector<Tile> tileSelection(static_cast<size_t>(Tile::Type::COUNT));

	// The tile map of the world ordered from left to right, then top to bottom.
	std::vector<Tile::Type> tiles(World::TILE_COUNT);

	Transform2D camera;

	void update()
	{
		for (iterator = entities.begin(); iterator != entities.end(); iterator++)
		{
			(*iterator)->update();
		}
	}

	void addEntity(Entity *entity)
	{
		entities.push_back(entity);
	}

	void setTile(Tile::Type tile, const glm::ivec2 &position)
	{
		tiles[World::TILE_WIDTH * position.y + position.x] = tile;
	}

	void setTile(Tile::Type tile, int x, int y)
	{
		tiles[World::TILE_WIDTH * y + x] = tile;
	}

	void setTile(Tile::Type tile, size_t index)
	{
		tiles[index] = tile;
	}

	Tile::Type getTile(const glm::ivec2 &position)
	{
		return tiles[World::TILE_WIDTH * position.y + position.x];
	}

	Tile::Type getTile(int x, int y)
	{
		return tiles[World::TILE_WIDTH * y + x];
	}

	Tile::Type getTile(size_t index)
	{
		return tiles[index];
	}

	const Tile &getTileSelectionAt(Tile::Type tile)
	{
		return tileSelection[static_cast<Tile::type_t>(tile)];
	}

	void loadTileSelection(const TextureAtlas &tileAtlas)
	{
		tileSelection[static_cast<size_t>(Tile::Type::DIRT)].name = "dirt";
		tileSelection[static_cast<size_t>(Tile::Type::GRASS)].name = "grass";
		tileSelection[static_cast<size_t>(Tile::Type::PARQUET_BRIGHT)].name = "parquet-bright";
		tileSelection[static_cast<size_t>(Tile::Type::PARQUET_DARK)].name = "parquet-dark";
		tileSelection[static_cast<size_t>(Tile::Type::SAND)].name = "sand";
		tileSelection[static_cast<size_t>(Tile::Type::STONE)].name = "stone";
		tileSelection[static_cast<size_t>(Tile::Type::STONE_PLATE)].name = "stone-plate";

		for (Tile::type_t i = 0; i < static_cast<Tile::type_t>(Tile::Type::COUNT); ++i)
		{
			tileSelection[i].color.r = 1.0f;
			tileSelection[i].color.g = 1.0f;
			tileSelection[i].color.b = 1.0f;
			tileSelection[i].color.a = 1.0f;

			tileSelection[i].textureRect = tileAtlas.getTexCoord(std::string(tileSelection[i].name));
		}
	}

	void loadTileMap(const char *fileName)
	{
		std::ifstream file(fileName, std::ios::binary);
		if (!file.good())
			return;

		tiles.resize(World::TILE_COUNT);
		file.read(reinterpret_cast<char *>(tiles.data()), sizeof(Tile::Type) * World::TILE_COUNT);

		file.close();
	}

	void saveTileMap(const char *fileName)
	{
		std::ofstream file(fileName, std::ios::binary);
		if (!file.good())
			return;

		tiles.resize(World::TILE_COUNT);
		file.write(reinterpret_cast<const char *>(tiles.data()), sizeof(Tile::Type) * World::TILE_COUNT);

		file.close();
	}

	void loadTileMapFromImage(const char *fileName)
	{
		sf::Image img;
		img.loadFromFile(fileName);

		if (img.getSize().x * img.getSize().y != World::TILE_COUNT)
			return;

		tiles.resize(World::TILE_COUNT);
		for (unsigned int y = 0; y < World::TILE_HEIGHT; ++y)
		{
			for (unsigned int x = 0; x < World::TILE_WIDTH; ++x)
			{
				sf::Color imgCol = img.getPixel(x, y);
				tiles[y * World::TILE_WIDTH + x] = getTileTypeFromColor(glm::vec3(imgCol.r / 255.0f, imgCol.g / 255.0f, imgCol.b / 255.0f));
			}
		}
	}

	Tile::Type getTileTypeFromColor(const glm::vec3 &color)
	{
		for (Tile::type_t i = 0; i < static_cast<Tile::type_t>(Tile::Type::COUNT); ++i)
		{
			if (getColorFromTileType(static_cast<Tile::Type>(i)) == color)
				return static_cast<Tile::Type>(i);
		}
		return static_cast<Tile::Type>(0);
	}

	glm::vec3 getColorFromTileType(Tile::Type type)
	{
		switch (type)
		{
		default:
			return glm::vec3(0.0f, 0.0f, 0.0f);
		case Tile::Type::DIRT:
			return glm::vec3(124.0f / 255.0f, 67.0f / 255.0f, 0.0f / 255.0f);
		case Tile::Type::GRASS:
			return glm::vec3(96.0f / 255.0f, 167.0f / 255.0f, 20.0f / 255.0f);
		case Tile::Type::PARQUET_BRIGHT:
			return glm::vec3(224.0f / 255.0f, 162.0f / 255.0f, 14.0f / 255.0f);
		case Tile::Type::PARQUET_DARK:
			return glm::vec3(244.0f / 255.0f, 162.0f / 255.0f, 14.0f / 255.0f);
		case Tile::Type::SAND:
			return glm::vec3(255.0f / 255.0f, 244.0f / 255.0f, 184.0f / 255.0f);
		case Tile::Type::STONE_PLATE:
			return glm::vec3(115.0f / 255.0f, 115.0f / 255.0f, 115.0f / 255.0f);
		case Tile::Type::STONE:
			return glm::vec3(182.0f / 255.0f, 182.0f / 255.0f, 182.0f / 255.0f);
		}
	}

	void genColorPalette(const char *fileName)
	{
		sf::Image img;
		img.create(World::TILE_PIXEL_WIDTH * static_cast<unsigned int>(Tile::Type::COUNT), World::TILE_PIXEL_HEIGHT, sf::Color(0, 0, 0, 0));

		for (Tile::type_t i = 0; i < static_cast<Tile::type_t>(Tile::Type::COUNT); ++i)
		{
			glm::vec3 color = getColorFromTileType(static_cast<Tile::Type>(i));
			sf::Color sfCol(static_cast<sf::Uint8>(color.r * 255.0f), static_cast<sf::Uint8>(color.g * 255.0f), static_cast<sf::Uint8>(color.b * 255.0f), 255);
			for (unsigned int y = 0; y < World::TILE_PIXEL_HEIGHT; ++y)
			{
				for (unsigned int x = 0; x < World::TILE_PIXEL_WIDTH; ++x)
				{
					img.setPixel(i * World::TILE_PIXEL_WIDTH + x, y, sfCol);
				}
			}
		}

		img.saveToFile(fileName);
	}

	float getLeftBorder(float screenWidth)
	{
		return (World::WIDTH_F - screenWidth) * -0.5f;
	}

	float getTopBorder(float screenHeight)
	{
		return (World::HEIGHT_F - screenHeight) * 0.5f;
	}

	float getRightBorder(float screenWidth)
	{
		return (World::WIDTH_F - screenWidth) * 0.5f;
	}

	float getBottomBorder(float screenHeight)
	{
		return (World::HEIGHT_F - screenHeight) * -0.5f;
	}
}