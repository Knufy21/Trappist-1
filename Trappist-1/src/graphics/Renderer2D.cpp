#include "Trappist-1\graphics\Renderer2D.hpp"

#include <Trappist-1\ui\widgets\Label.hpp>
#include <Trappist-1\graphics\Shader.hpp>

Renderer2D::Renderer2D()
	: vertexCount(0), indexCount(0), activeTextureSlotCount(0), transformationStackTop(0), scissorStackTop(0), activeFontAtlasSlotCount(0), fontVertexCount(0), fontIndexCount(0)
{
	createBuffers();

	// Put indentity matrix into stack at first
	transformationStack[transformationStackTop] = glm::mat3();
}

Renderer2D::~Renderer2D()
{
	deleteBuffers();
}

void Renderer2D::setShader(Shader *shader)
{
	this->shader = shader;
	shader->enable();
	std::string s("textures[");
	for (int i = 0; i < 32; ++i)
		shader->setUniform1i((s + std::to_string(i) + "]").c_str(), i);
	shader->disable();
}

void Renderer2D::setFontShader(Shader *fontShader)
{
	this->fontShader = fontShader;
	fontShader->enable();
	std::string s("textures[");
	for (int i = 0; i < 32; ++i)
		fontShader->setUniform1i((s + std::to_string(i) + "]").c_str(), i);
	fontShader->disable();
}

void Renderer2D::setLightMap(GLuint texture)
{
	this->lightMap = lightMap;
}

void Renderer2D::createBuffers()
{
	glGenVertexArrays(1, &dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VAO_INDEX]);
	glGenBuffers(2, &dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VERTEX_DATA_VBO_INDEX]);

	glBindVertexArray(dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VAO_INDEX]);

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VERTEX_DATA_VBO_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, Renderer2D::MAX_ELEMENT_VERTEX_DATA_BUFFER_SIZE, nullptr, GL_STREAM_DRAW);
	setVertexDataAttribLocations();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_INDEX_VBO_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Renderer2D::MAX_ELEMENT_INDEX_DATA_BUFFER_SIZE, nullptr, GL_STREAM_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer2D::deleteBuffers()
{
	glDeleteVertexArrays(1, &dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VAO_INDEX]);
	glDeleteBuffers(2, &dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VERTEX_DATA_VBO_INDEX]);
}

void Renderer2D::begin()
{
	vertexCount = 0;
	indexCount = 0;
	fontVertexCount = 0;
	fontIndexCount = 0;

	//texts.clear();
	labels.clear();
	//sprites.clear();
	//scissors.clear();

	glGetIntegerv(GL_VIEWPORT, viewport);
	scissorStack[0] = { viewport[0], viewport[1], viewport[2], viewport[3] };

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VERTEX_DATA_VBO_INDEX]);
	vertexBuffer = static_cast<VertexBuffer*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
	fontVertexBuffer = vertexBuffer + Renderer2D::FONT_VERTEX_BUFFER_OFFSET;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_INDEX_VBO_INDEX]);
	indexBuffer = static_cast<ELEMENT_INDEX_GL_TYPE*>(glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY));
	fontIndexBuffer = indexBuffer + Renderer2D::FONT_INDEX_BUFFER_OFFSET;
}

void Renderer2D::submit(const VertexPCT2D *vertices, GLuint vertexCount, const ELEMENT_INDEX_GL_TYPE *indices, GLuint indexCount, const Texture *texture, float depth)
{
	float textureSlot = submitTexture(texture);

	for (size_t i = 0; i < vertexCount; ++i)
	{
		vertexBuffer->vertexData.vertex = vertices[i];
		vertexBuffer->vertexData.textureSlot = textureSlot;
		glm::vec2 pos = this->offset + glm::vec2(transformationStack[transformationStackTop] * glm::vec3(vertices[i].position.x, vertices[i].position.y, 1.0f));
		vertexBuffer->vertexData.vertex.position.x = ((pos.x / static_cast<float>(viewport[2])) - 0.5f) * 2.0f;
		vertexBuffer->vertexData.vertex.position.y = ((pos.y / static_cast<float>(viewport[3])) - 0.5f) * -2.0f;
		vertexBuffer->vertexData.depth = depth;
		++vertexBuffer;
	}

	for (size_t i = 0; i < indexCount; ++i)
	{
		(*indexBuffer) = this->vertexCount + indices[i];
		++indexBuffer;
	}

	this->vertexCount += vertexCount;
	this->indexCount += indexCount;

	// Push back sprite index count
	//sprites.push_back(indexCount);
	//scissors.push_back(scissorStack[scissorStackTop]);
}

//void Renderer2D::submit(const Mesh2D &mesh, const Texture *texture)
//{
//	submit(mesh.vertices.data(), mesh.vertices.size(), mesh.indices.data(), mesh.indices.size(), texture);
//}

void Renderer2D::submit4(const VertexPCT2D *vertices, const Texture *texture, float depth)
{
	float textureSlot = submitTexture(texture);

	for (size_t i = 0; i < 4; ++i)
	{
		vertexBuffer->vertexData.vertex = vertices[i];
		vertexBuffer->vertexData.textureSlot = textureSlot;
		glm::vec3 pos = /*this->offset + */(transformationStack[transformationStackTop] * glm::vec3(vertices[i].position.x, vertices[i].position.y, 1.0f));
		// pixel data can be castet to int because of floating points are inaccurat
		vertexBuffer->vertexData.vertex.position.x = ((static_cast<float>(static_cast<int>(pos.x)) / static_cast<float>(viewport[2])) - 0.5f) * 2.0f;
		vertexBuffer->vertexData.vertex.position.y = ((static_cast<float>(static_cast<int>(pos.y)) / static_cast<float>(viewport[3])) - 0.5f) * -2.0f;
		vertexBuffer->vertexData.depth = depth;
		++vertexBuffer;
	}

	(*indexBuffer) = this->vertexCount;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 1;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 2;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 2;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 3;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount;
	++indexBuffer;

	this->vertexCount += 4;
	this->indexCount += 6;

	// Push back sprite index count
	//sprites.push_back(6);
	//scissors.push_back(scissorStack[scissorStackTop]);
}

void Renderer2D::submit16(const VertexPCT2D *vertices, const Texture *texture, float depth)
{
	float textureSlot = submitTexture(texture);

	for (size_t i = 0; i < 16; ++i)
	{
		vertexBuffer->vertexData.vertex = vertices[i];
		vertexBuffer->vertexData.textureSlot = textureSlot;
		glm::vec2 pos = this->offset + glm::vec2(transformationStack[transformationStackTop] * glm::vec3(vertices[i].position.x, vertices[i].position.y, 1.0f));
		vertexBuffer->vertexData.vertex.position.x = ((static_cast<float>(static_cast<int>(pos.x)) / static_cast<float>(viewport[2])) - 0.5f) * 2.0f;
		vertexBuffer->vertexData.vertex.position.y = ((static_cast<float>(static_cast<int>(pos.y)) / static_cast<float>(viewport[3])) - 0.5f) * -2.0f;
		vertexBuffer->vertexData.depth = depth;
		++vertexBuffer;
	}

	// Quad 0
	(*indexBuffer) = this->vertexCount + 0;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 4;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 1;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 4;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 5;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 1;
	++indexBuffer;

	// Quad 1
	(*indexBuffer) = this->vertexCount + 1;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 5;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 2;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 5;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 6;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 2;
	++indexBuffer;

	// Quad 2
	(*indexBuffer) = this->vertexCount + 2;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 6;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 3;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 6;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 7;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 3;
	++indexBuffer;

	// Quad 3
	(*indexBuffer) = this->vertexCount + 4;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 8;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 5;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 5;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 8;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 9;
	++indexBuffer;

	// Quad 4
	(*indexBuffer) = this->vertexCount + 5;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 9;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 6;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 9;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 10;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 6;
	++indexBuffer;

	// Quad 5
	(*indexBuffer) = this->vertexCount + 6;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 10;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 7;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 10;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 11;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 7;
	++indexBuffer;

	// Quad 6
	(*indexBuffer) = this->vertexCount + 8;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 12;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 9;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 12;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 13;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 9;
	++indexBuffer;

	// Quad 7
	(*indexBuffer) = this->vertexCount + 9;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 13;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 10;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 13;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 14;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 10;
	++indexBuffer;

	// Quad 8
	(*indexBuffer) = this->vertexCount + 10;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 14;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 11;
	++indexBuffer;

	(*indexBuffer) = this->vertexCount + 14;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 15;
	++indexBuffer;
	(*indexBuffer) = this->vertexCount + 11;
	++indexBuffer;

	this->vertexCount += 16;
	this->indexCount += 48;

	// Push back sprite index count
	//sprites.push_back(48);
	//scissors.push_back(scissorStack[scissorStackTop]);
}

//void Renderer2D::submitText(const Text &text)
//{
//	float fontAtlasSlot = submitFontAtlas(&text.getFont().getTextureAtlas());
//
//	for (size_t i = 0; i < text.getVertices().size(); ++i)
//	{
//		fontVertexBuffer->vertexData.vertex = text.getVertices()[i];
//		fontVertexBuffer->vertexData.textureSlot = fontAtlasSlot;
//		glm::vec2 pos = this->offset + glm::vec2(transformationStack[transformationStackTop] * glm::vec3(text.getVertices()[i].position.x, text.getVertices()[i].position.y, 1.0f));
//		fontVertexBuffer->vertexData.vertex.position.x = ((static_cast<float>(static_cast<int>(pos.x)) / viewport[2]) - 0.5f) * 2.0f;
//		fontVertexBuffer->vertexData.vertex.position.y = ((static_cast<float>(static_cast<int>(pos.y)) / viewport[3]) - 0.5f) * -2.0f;
//		++fontVertexBuffer;
//	}
//
//	for (size_t i = 0; i < text.getIndices().size(); ++i)
//	{
//		(*fontIndexBuffer) = RENDERER2D_FONT_VERTEX_BUFFER_OFFSET + this->fontVertexCount + text.getIndices()[i];
//		++fontIndexBuffer;
//	}
//
//	texts.push_back(&text);
//
//	this->fontVertexCount += text.getVertices().size();
//	this->fontIndexCount += text.getIndices().size();
//
//	textScissors.push_back(scissorStack[scissorStackTop]);
//}

void Renderer2D::submitLabel(const ui::Label &label)
{
	float fontAtlasSlot = submitFontAtlas(&label.getFont().getTextureAtlas());

	for (size_t i = 0; i < label.getTextVertices().size(); ++i)
	{
		fontVertexBuffer->vertexData.vertex = label.getTextVertices()[i];
		fontVertexBuffer->vertexData.textureSlot = fontAtlasSlot;
		glm::vec2 pos = this->offset + glm::vec2(transformationStack[transformationStackTop] * glm::vec3(label.getTextVertices()[i].position.x, label.getTextVertices()[i].position.y, 1.0f));
		fontVertexBuffer->vertexData.vertex.position.x = ((static_cast<float>(static_cast<int>(pos.x)) / static_cast<float>(viewport[2])) - 0.5f) * 2.0f;
		fontVertexBuffer->vertexData.vertex.position.y = ((static_cast<float>(static_cast<int>(pos.y)) / static_cast<float>(viewport[3])) - 0.5f) * -2.0f;
		++fontVertexBuffer;
	}

	for (size_t i = 0; i < label.getTextIndices().size(); ++i)
	{
		(*fontIndexBuffer) = Renderer2D::FONT_VERTEX_BUFFER_OFFSET + this->fontVertexCount + label.getTextIndices()[i];
		++fontIndexBuffer;
	}

	labels.push_back(&label);

	this->fontVertexCount += label.getTextVertices().size();
	this->fontIndexCount += label.getTextIndices().size();

	//textScissors.push_back(scissorStack[scissorStackTop]);
}

void Renderer2D::end()
{
	if (!glUnmapBuffer(GL_ARRAY_BUFFER))
		printf("Couldn't unmap dataBuffers[RENDERER2D_DATA_BUFFERS_ELEMENT_VERTEX_DATA_VBO_INDEX]!\n");
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	if (!glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER))
		printf("Couldn't unmap dataBuffers[RENDERER2D_DATA_BUFFERS_ELEMENT_INDEX_VBO_INDEX]!\n");;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer2D::flush()
{
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_CULL_FACE);
	//glEnable(GL_SCISSOR_TEST);

	// Flush standard vertices
	if (shader)
		shader->enable();

	for (GLubyte i = 0; i < activeTextureSlotCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureSlots[i]);
		//textureSlots[i] = 0.0f;
		textureSlots[i] = 0;
	}
	activeTextureSlotCount = 0;

	glBindVertexArray(dataBuffers[Renderer2D::DATA_BUFFERS_ELEMENT_VAO_INDEX]);
	//glScissor(0, 0, 400, 424);
	//unsigned int indexOffset = 0;
	//for (size_t i = 0; i < sprites.size(); ++i)
	//{
	//	glScissor(scissors[i].x, scissors[i].y, scissors[i].width, scissors[i].height);
	//	glDrawElements(GL_TRIANGLES, sprites[i], RENDERER2D_ELEMENT_INDEX_GL_MACRO_TYPE, reinterpret_cast<void*>(indexOffset * sizeof(RENDERER2D_ELEMENT_INDEX_GL_MACRO_TYPE)));
	//	indexOffset += sprites[i];
	//}

	glDrawElements(GL_TRIANGLES, indexCount, Renderer2D::ELEMENT_INDEX_GL_MACRO_TYPE, 0);

	// Flush font vertices

	if (fontShader)
		fontShader->enable();
	
	for (GLubyte i = 0; i < activeFontAtlasSlotCount; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, fontAtlasSlots[i]);
		//fontAtlasSlots[i] = 0.0f;
		fontAtlasSlots[i] = 0;
	}
	activeFontAtlasSlotCount = 0;
	
	size_t indexOffset = Renderer2D::FONT_INDEX_BUFFER_OFFSET;
	for (size_t i = 0; i < labels.size(); ++i)
	{
		//glScissor(textScissors[i].x, textScissors[i].y, textScissors[i].width, textScissors[i].height);
	
		// Set Textproperties
		constexpr float mul = 16.0f / 26.0f; // change the second value for adjustments (the bigger the more smooth)
		float edgeSize = 1.0f / (static_cast<float>(labels[i]->getFontSize()) * mul);
		fontShader->setUniform1f("thickness", labels[i]->getTextThickness());
		fontShader->setUniform4f("color", labels[i]->getTextColor());
		fontShader->setUniform1f("edge", edgeSize);
		fontShader->setUniform1f("outlineThickness", (labels[i]->getTextOutlineThickness() == 0.0f) ? 0.0f : labels[i]->getTextOutlineThickness() + labels[i]->getTextThickness());
		fontShader->setUniform4f("outlineColor", labels[i]->getTextOutlineColor());
		fontShader->setUniform2f("outlineOffset", labels[i]->getTextOutlineOffset());
		fontShader->setUniform1f("outlineEdge", edgeSize + labels[i]->getTextOutlineBlur());
		//reinterpret_cast<FontShader*>(fontShader)->setColor(labels[i]->getTextColor());
		//reinterpret_cast<FontShader*>(fontShader)->setEdge(edgeSize);
		//reinterpret_cast<FontShader*>(fontShader)->setOutlineThickness((labels[i]->getTextOutlineThickness() == 0.0f) ? 0.0f : labels[i]->getTextOutlineThickness() + labels[i]->getTextThickness()/* + edgeSize*/);
		//reinterpret_cast<FontShader*>(fontShader)->setOutlineColor(labels[i]->getTextOutlineColor());
		//reinterpret_cast<FontShader*>(fontShader)->setOutlineOffset(labels[i]->getTextOutlineOffset());
		//reinterpret_cast<FontShader*>(fontShader)->setOutlineEdge(edgeSize + labels[i]->getTextOutlineBlur());
	
		glDrawElements(GL_TRIANGLES, labels[i]->getTextIndices().size(), Renderer2D::ELEMENT_INDEX_GL_MACRO_TYPE, reinterpret_cast<void*>(indexOffset * sizeof(Renderer2D::ELEMENT_INDEX_GL_MACRO_TYPE)));
		indexOffset += labels[i]->getTextIndices().size();
	}

	//(GL_TRIANGLES, fontIndexCount, RENDERER2D_ELEMENT_INDEX_GL_MACRO_TYPE, reinterpret_cast<void*>(RENDERER2D_FONT_INDEX_BUFFER_OFFSET * sizeof(RENDERER2D_ELEMENT_INDEX_GL_MACRO_TYPE)));
	glBindVertexArray(0);

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glDisable(GL_SCISSOR_TEST);
}

float Renderer2D::submitTexture(const Texture *texture)
{
	float textureSlot = Renderer2D::TEXTURE_SLOT_INDEX_NO_TEXTURE;
	if (texture != nullptr && texture->getHandle() > 0)
	{
		bool found = false;
		for (GLubyte i = 0; i < activeTextureSlotCount; ++i)
		{
			if (textureSlots[i] == texture->getHandle())
			{
				found = true;
				textureSlot = i + 0.5f;
				break;
			}
		}

		if (!found)
		{
			if (activeTextureSlotCount >= Renderer2D::TEXTURE_SLOT_COUNT)
			{
				end();
				flush();
				begin();
			}
			textureSlots[activeTextureSlotCount++] = texture->getHandle();
			textureSlot = activeTextureSlotCount - 0.5f;
		}
	}
	return textureSlot;
}

float Renderer2D::submitFontAtlas(const Texture *texture)
{
	float textureSlot = Renderer2D::TEXTURE_SLOT_INDEX_NO_TEXTURE;
	if (texture != nullptr && texture->getHandle() > 0)
	{
		bool found = false;
		for (GLubyte i = 0; i < activeFontAtlasSlotCount; ++i)
		{
			if (fontAtlasSlots[i] == texture->getHandle())
			{
				found = true;
				textureSlot = i + 0.5f;
				break;
			}
		}

		if (!found)
		{
			if (activeFontAtlasSlotCount >= Renderer2D::TEXTURE_SLOT_COUNT)
			{
				end();
				flush();
				begin();
			}
			fontAtlasSlots[activeFontAtlasSlotCount++] = texture->getHandle();
			textureSlot = activeFontAtlasSlotCount - 0.5f;
		}
	}
	return textureSlot;
}

void Renderer2D::setVertexDataAttribLocations()
{
	glEnableVertexAttribArray(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_POSITION);
	glVertexAttribPointer(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_POSITION, sizeof(vertexBuffer->vertexData.vertex.position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, vertexData.vertex.position)));

	glEnableVertexAttribArray(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_COLOR);
	glVertexAttribPointer(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_COLOR, sizeof(vertexBuffer->vertexData.vertex.color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, vertexData.vertex.color)));

	glEnableVertexAttribArray(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_TEXCOORD);
	glVertexAttribPointer(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_TEXCOORD, sizeof(vertexBuffer->vertexData.vertex.texCoord) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, vertexData.vertex.texCoord)));

	glEnableVertexAttribArray(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_TEXTURE_SLOT);
	glVertexAttribPointer(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_TEXTURE_SLOT, 1, GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, vertexData.textureSlot)));

	glEnableVertexAttribArray(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_DEPTH);
	glVertexAttribPointer(Renderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_DEPTH, 1, GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, vertexData.depth)));
}

void Renderer2D::pushMatrix(const glm::mat3 &matrix)
{
	transformationStack[transformationStackTop + 1] = transformationStack[transformationStackTop] * matrix;
	++transformationStackTop;
}

void Renderer2D::popMatrix()
{
	--transformationStackTop;
}

void Renderer2D::pushScissor(GLint x, GLint y, GLint width, GLint height)
{
	scissorStack[++scissorStackTop] = { x, viewport[3] - y - height, width, height };
}

void Renderer2D::popScissor()
{
	--scissorStackTop;
}