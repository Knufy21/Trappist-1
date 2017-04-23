#pragma once

#include <vector>

#include <Trappist-1\graphics\Transform2D.hpp>
#include <Trappist-1\Tile.hpp>

class Entity;
namespace World
{
	static constexpr int TILE_PIXEL_WIDTH = 60;
	static constexpr int TILE_PIXEL_HEIGHT = 60;

	static constexpr float TILE_PIXEL_WIDTH_F = static_cast<float>(TILE_PIXEL_WIDTH);
	static constexpr float TILE_PIXEL_HEIGHT_F = static_cast<float>(TILE_PIXEL_HEIGHT);

	static constexpr int TILE_WIDTH = 64;
	static constexpr int TILE_HEIGHT = 36;

	static constexpr float TILE_WIDTH_F = static_cast<float>(TILE_WIDTH);
	static constexpr float TILE_HEIGHT_F = static_cast<float>(TILE_HEIGHT);

	static constexpr int WIDTH = TILE_WIDTH * TILE_PIXEL_WIDTH;
	static constexpr int HEIGHT = TILE_HEIGHT * TILE_PIXEL_HEIGHT;

	static constexpr float WIDTH_F = static_cast<float>(WIDTH);
	static constexpr float HEIGHT_F = static_cast<float>(HEIGHT);

	static constexpr float HALF_WIDTH_F = WIDTH_F * 0.5f;
	static constexpr float HALF_HEIGHT_F = HEIGHT_F * 0.5f;

	static constexpr int TILE_COUNT = TILE_WIDTH * TILE_HEIGHT;

	// Updates all Entities
	void update();

	// Adds the entity to the vector of entities.
	void addEntity(Entity *entity);

	// Sets the specified tile type at the specified position.
	void setTile(Tile::Type tile, const glm::ivec2 &position);

	// Sets the specified tile type at the specified x and y position.
	void setTile(Tile::Type tile, int x, int y);

	// Sets the specified tile type at the specified index.
	void setTile(Tile::Type tile, size_t index);

	// Returns the tile type at the specified position.
	Tile::Type getTile(const glm::ivec2 &position);

	// Returns the tile type at the specified x and y position.
	Tile::Type getTile(int x, int y);

	// Returns the tile type at the specified index.
	Tile::Type getTile(size_t index);

	// Returns the tile from the loaded tile set at the specified tile type.
	const Tile &getTileSelectionAt(Tile::Type tile);

	// Loads the tile selection with the specified tile atlas
	void loadTileSelection(const TextureAtlas &tileAtlas);

	// Loads the tile map from the specified file.
	void loadTileMap(const char *fileName);

	// Saves the tile map to the specified file.
	void saveTileMap(const char *fileName);

	// Loads the tile map from the specified png image.
	void loadTileMapFromImage(const char *fileName);

	// Returns the tile associated with the specified color. (Very inefficient)
	Tile::Type getTileTypeFromColor(const glm::vec3 &color);

	// Returns the color associated with the specified tile type.
	glm::vec3 getColorFromTileType(Tile::Type type);

	void genColorPalette(const char *fileName);

	float getLeftBorder(float screenWidth);
	float getTopBorder(float screenHeight);
	float getRightBorder(float screenWidth);
	float getBottomBorder(float screenHeight);

	extern std::vector<Entity*> entities;

	extern Transform2D camera;
}
