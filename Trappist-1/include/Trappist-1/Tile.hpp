#pragma once

#include <Trappist-1\graphics\Transform2D.hpp>
#include <Trappist-1\graphics\Texture.hpp>
#include <Trappist-1\graphics\Vertex2D.hpp>
#include <Trappist-1\TextureManager.hpp>

class Tile
{
public:
	using type_t = unsigned char;

	enum class Type : type_t
	{
		DIRT,
		GRASS,
		PARQUET_BRIGHT,
		PARQUET_DARK,
		SAND,
		STONE,
		STONE_PLATE,

		COUNT
	};

	const char *name;
	sf::FloatRect textureRect;
	glm::vec4 color;

	Tile();
private:
	Tile(const Tile&) = delete;
	Tile(Tile&&) = delete;

	Tile &operator=(const Tile&) = delete;
	Tile &operator=(Tile&&) = delete;
};

inline Tile::Tile()
	: name(nullptr), textureRect(0.0f, 0.0f, 1.0f, 1.0f), color(1.0f, 1.0f, 1.0f, 1.0f)
{	}

