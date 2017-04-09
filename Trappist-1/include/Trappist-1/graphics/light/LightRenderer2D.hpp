#pragma once

#include <GL\glew.h>
#include <Trappist-1\graphics\Shader.hpp>
#include <Trappist-1\graphics\light\Light2D.hpp>

class LightRenderer2D
{
	struct VertexBuffer
	{
		Light2D light;
	};

	// Buffer index defs
	static constexpr GLuint DATA_BUFFERS_ARRAY_VAO_INDEX				=	0;
	static constexpr GLuint DATA_BUFFERS_ARRAY_VERTEX_DATA_VBO_INDEX	=	1;
	static constexpr GLuint DATA_BUFFERS_FBO_INDEX						=	2;
	static constexpr GLuint DATA_BUFFERS_CBO_INDEX						=	3;
	static constexpr GLuint DATA_BUFFER_COUNT							=	4;
	// Max buffer size defs
	static constexpr GLsizeiptr MAX_ELEMENT_VERTEX_DATA_BUFFER_SIZE		=	1'000 * sizeof(VertexBuffer);
	// Vertex attrib locations
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_POSITION		=	0;
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_COLOR			=	1;
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_EDGES			=	2;
	// TransformationStack
	static constexpr size_t TRANSFORMATION_STACK_SIZE					=	10;
public:
	LightRenderer2D();
	~LightRenderer2D();

	// Sets the shader being used to render lights.
	void setShader(Shader *shader);

	// Returns the shader being used to render lights.
	Shader *getShader();

	// Sets the default light color.
	void setDefaultLightColor(const glm::vec4 &defaultLightColor);

	// Begins the submittion.
	void begin();

	// Pushes the specified matrix multiplied with the top matrix onto the transformation stack.
	void pushMatrix(const glm::mat3 &matrix);

	// Pops the top matrix from the transformation stack.
	void popMatrix();

	// Submits a light2d int the render cache.
	void submitLight2D(const glm::vec2 &position, const glm::vec4 &color, const glm::vec2 &edges);

	// Ends the submittion.
	void end();

	// Takes all cached information and renders it.
	void flush();

	// Returns the color texture attachment of the light renderer2d.
	GLuint getColorTextureAttachment() const;

protected:
	// Creates and sets the attribute locations of all buffers.
	void createBuffers();

	// Deletes all buffers.
	void deleteBuffers();

	// Creates the color texture attachment with the specified width and height.
	void createColorTextureAttachment(GLsizei width, GLsizei height);

	// Deletes the color texture attachment.
	void deleteColorTextureAttachment();

	// Sets the vertex data attribute locations for the currently bound vao.
	void setVertexDataAttribLocations();

private:
	// vao, vertex data vbo, element index vbo
	GLuint dataBuffers[LightRenderer2D::DATA_BUFFER_COUNT];

	VertexBuffer *vertexBuffer;
	GLsizei vertexCount;

	GLuint screenWidth, screenHeight;

	Shader *lightShader;

	// Viewport information for position transforming
	GLint viewport[4];

	// TransformationStack
	GLubyte transformationStackTop;
	glm::mat3 transformationStack[LightRenderer2D::TRANSFORMATION_STACK_SIZE];

	glm::vec4 defaultLightColor;
};

// Inline

inline void LightRenderer2D::setShader(Shader *shader)
{
	this->lightShader = shader;
}

inline Shader *LightRenderer2D::getShader()
{
	return this->lightShader;
}

inline void LightRenderer2D::setDefaultLightColor(const glm::vec4 &defaultLightColor)
{
	this->defaultLightColor = defaultLightColor;
}

inline GLuint LightRenderer2D::getColorTextureAttachment() const
{
	return this->dataBuffers[LightRenderer2D::DATA_BUFFERS_CBO_INDEX];
}