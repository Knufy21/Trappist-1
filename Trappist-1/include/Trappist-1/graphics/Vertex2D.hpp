#pragma once

#include <glm\glm.hpp>

struct VertexPT2D
{
	glm::vec2 position;
	glm::vec2 texCoord;
};

struct VertexPCT2D
{
	glm::vec2 position;
	glm::vec4 color;
	glm::vec2 texCoord;
};