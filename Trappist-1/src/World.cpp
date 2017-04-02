#include <Trappist-1\World.hpp>
#include <Trappist-1\entities\Entity.hpp>

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