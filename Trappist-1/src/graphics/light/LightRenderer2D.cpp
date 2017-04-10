#include <Trappist-1\graphics\light\LightRenderer2D.hpp>
#include <iostream>

LightRenderer2D::LightRenderer2D()
	: screenWidth(0), screenHeight(0), lightShader(nullptr)
{
	createBuffers();
}

LightRenderer2D::~LightRenderer2D()
{
	deleteBuffers();
}

void LightRenderer2D::begin()
{
	glGetIntegerv(GL_VIEWPORT, viewport);

	if (this->screenWidth != viewport[2] || this->screenHeight != viewport[3])
	{
		this->screenWidth = viewport[2];
		this->screenHeight = viewport[3];
		createColorTextureAttachment(screenWidth, screenHeight);
	}

	vertexCount = 0;

	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[LightRenderer2D::DATA_BUFFERS_ARRAY_VERTEX_DATA_VBO_INDEX]);
	vertexBuffer = static_cast<VertexBuffer *>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
}

void LightRenderer2D::pushMatrix(const glm::mat3 &matrix)
{
	transformationStack[transformationStackTop + 1] = transformationStack[transformationStackTop] * matrix;
	++transformationStackTop;
}

void LightRenderer2D::popMatrix()
{
	--transformationStackTop;
}

void LightRenderer2D::submitLight2D(const glm::vec2 &position, const glm::vec4 &color, const glm::vec2 &edges)
{
	vertexBuffer->light.position = position;
	glm::vec3 pos = (transformationStack[transformationStackTop] * glm::vec3(position.x, position.y, 1.0f));
	vertexBuffer->light.position.x = ((static_cast<float>(static_cast<int>(pos.x)) / static_cast<float>(viewport[2])) - 0.5f) * 2.0f;
	vertexBuffer->light.position.y = ((static_cast<float>(static_cast<int>(pos.y)) / static_cast<float>(viewport[3])) - 0.5f) * -2.0f;
	vertexBuffer->light.color = color;
	vertexBuffer->light.edges = edges;
	++vertexBuffer;

	++vertexCount;
}

void LightRenderer2D::end()
{
	if (!glUnmapBuffer(GL_ARRAY_BUFFER))
		printf("Couldn't unmap dataBuffers[LightRenderer2D::DATA_BUFFERS_ARRAY_VERTEX_DATA_VBO_INDEX]!\n");
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void LightRenderer2D::flush()
{
	glEnable(GL_PROGRAM_POINT_SIZE);
	glEnable(GL_POINT_SPRITE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	glBindFramebuffer(GL_FRAMEBUFFER, dataBuffers[LightRenderer2D::DATA_BUFFERS_FBO_INDEX]);
	glClearColor(defaultLightColor.r, defaultLightColor.g, defaultLightColor.b, defaultLightColor.a);
	glClear(GL_COLOR_BUFFER_BIT);

	lightShader->enable();

	glBindVertexArray(dataBuffers[LightRenderer2D::DATA_BUFFERS_ARRAY_VAO_INDEX]);
	glDrawArrays(GL_POINTS, 0, vertexCount);
	glBindVertexArray(0);

	lightShader->disable();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glDisable(GL_BLEND);
}

void LightRenderer2D::createColorTextureAttachment(GLsizei width, GLsizei height)
{
	deleteColorTextureAttachment();

	glBindFramebuffer(GL_FRAMEBUFFER, dataBuffers[LightRenderer2D::DATA_BUFFERS_FBO_INDEX]);

	glGenTextures(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_CBO_INDEX);
	glBindTexture(GL_TEXTURE_2D, dataBuffers[LightRenderer2D::DATA_BUFFERS_CBO_INDEX]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dataBuffers[LightRenderer2D::DATA_BUFFERS_CBO_INDEX], 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void LightRenderer2D::deleteColorTextureAttachment()
{
	if (glIsTexture(dataBuffers[LightRenderer2D::DATA_BUFFERS_CBO_INDEX]))
		glDeleteTextures(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_CBO_INDEX);
}

void LightRenderer2D::createBuffers()
{
	glGenVertexArrays(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_ARRAY_VAO_INDEX);
	glGenBuffers(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_ARRAY_VERTEX_DATA_VBO_INDEX);
	glGenFramebuffers(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_FBO_INDEX);

	glBindVertexArray(dataBuffers[LightRenderer2D::DATA_BUFFERS_ARRAY_VAO_INDEX]);

	// Create and setup vbo
	glBindBuffer(GL_ARRAY_BUFFER, dataBuffers[LightRenderer2D::DATA_BUFFERS_ARRAY_VERTEX_DATA_VBO_INDEX]);
	glBufferData(GL_ARRAY_BUFFER, LightRenderer2D::MAX_ELEMENT_VERTEX_DATA_BUFFER_SIZE, nullptr, GL_STREAM_DRAW);
	setVertexDataAttribLocations();

	// Create and setup fbo
	//glBindFramebuffer(GL_FRAMEBUFFER, dataBuffers[LightRenderer2D::DATA_BUFFERS_FBO_INDEX]);
	//createColorTextureAttachment(800, 480);

	//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, dataBuffers[LightRenderer2D::DATA_BUFFERS_CBO_INDEX], 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void LightRenderer2D::deleteBuffers()
{
	deleteColorTextureAttachment();
	glDeleteFramebuffers(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_FBO_INDEX);
	glDeleteBuffers(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_ARRAY_VERTEX_DATA_VBO_INDEX);
	glDeleteVertexArrays(1, dataBuffers + LightRenderer2D::DATA_BUFFERS_ARRAY_VAO_INDEX);
}

void LightRenderer2D::setVertexDataAttribLocations()
{
	glEnableVertexAttribArray(LightRenderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_POSITION);
	glVertexAttribPointer(LightRenderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_POSITION, sizeof(vertexBuffer->light.position) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, light.position)));

	glEnableVertexAttribArray(LightRenderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_COLOR);
	glVertexAttribPointer(LightRenderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_COLOR, sizeof(vertexBuffer->light.color) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, light.color)));

	glEnableVertexAttribArray(LightRenderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_EDGES);
	glVertexAttribPointer(LightRenderer2D::VERTEX_ATTRIB_LOCATION_VERTEX_EDGES, sizeof(vertexBuffer->light.edges) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(VertexBuffer), (GLvoid*)(offsetof(VertexBuffer, light.edges)));
}