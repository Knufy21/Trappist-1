#pragma once

#include <glm\glm.hpp>

//namespace
//{
	struct CharacterInfo
	{
		glm::vec2 size;
		glm::vec2 texCoord;
		glm::vec2 texSize;
		glm::vec2 offset;
		float advance;
	};

	struct Character
	{
		unsigned short ascii;
		CharacterInfo info;
	};
//}