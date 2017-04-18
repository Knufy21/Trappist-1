#pragma once

#include <vector>
#include <GL\glew.h>
#include <Trappist-1\graphics\Vertex2D.hpp>
#include <Trappist-1\graphics\Texture.hpp>

namespace ui { class Label; }
class Shader;
class Renderer2D
{
	struct VertexPCTT2D
	{
		VertexPCT2D vertex;
		float textureSlot;
		float depth;
	};

	struct VertexBuffer
	{
		VertexPCTT2D vertexData;
	};

	struct Scissor
	{
		GLint x;
		GLint y;
		GLint width;
		GLint height;
	};

	// Type defs
	using ELEMENT_INDEX_GL_TYPE											=	GLuint;
	static constexpr GLenum ELEMENT_INDEX_GL_MACRO_TYPE					=	GL_UNSIGNED_INT;
	// Buffer index defs
	static constexpr GLuint DATA_BUFFERS_ELEMENT_VAO_INDEX				=	0;
	static constexpr GLuint DATA_BUFFERS_ELEMENT_VERTEX_DATA_VBO_INDEX	=	1;
	static constexpr GLuint DATA_BUFFERS_ELEMENT_INDEX_VBO_INDEX		=	2;
	// Max buffer size defs
	static constexpr GLsizeiptr FONT_VERTEX_BUFFER_OFFSET				=	500'000;
	static constexpr GLsizeiptr FONT_INDEX_BUFFER_OFFSET				=	500'000;
	static constexpr GLsizeiptr MAX_ELEMENT_VERTEX_DATA_BUFFER_SIZE		=	Renderer2D::FONT_VERTEX_BUFFER_OFFSET * sizeof(VertexBuffer) + 100'000 * sizeof(VertexBuffer);
	static constexpr GLsizeiptr MAX_ELEMENT_INDEX_DATA_BUFFER_SIZE		=	Renderer2D::FONT_INDEX_BUFFER_OFFSET * sizeof(ELEMENT_INDEX_GL_TYPE) + 100'000 * sizeof(ELEMENT_INDEX_GL_TYPE);
	// Vertex attrib locations
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_POSITION		=	0;
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_COLOR			=	1;
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_TEXCOORD		=	2;
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_TEXTURE_SLOT	=	3;
	static constexpr GLuint VERTEX_ATTRIB_LOCATION_VERTEX_DEPTH			=	4;
	// Textures
	static constexpr size_t TEXTURE_SLOT_COUNT							=	32;
	static constexpr float TEXTURE_SLOT_INDEX_NO_TEXTURE				=	0.0f;
	// TransformationStack
	static constexpr size_t TRANSFORMATION_STACK_SIZE					=	10;
	static constexpr size_t SCISSOR_STACK_SIZE							=	10;
public:
	Renderer2D();
	~Renderer2D();

	// Sets the shader being used to render everything but fonts.
	void setShader(Shader *shader);

	// Sets the shader being used to render fonts.
	void setFontShader(Shader *fontShader);

	// Returns the color used to clear the color buffer.
	const glm::vec4 &getClearColor() const;

	// Sets the color used to clear the color buffer.
	void setClearColor(const glm::vec4 &clearColor);

	// Sets the color used to clear the color buffer.
	void setClearColor(float r, float g, float b, float a);

	// Pushes the specified matrix multiplied with the top matrix onto the transformation stack.
	void pushMatrix(const glm::mat3 &matrix);

	// Pops the top matrix from the transformation stack.
	void popMatrix();

	void setLightMap(GLuint texture);

	// Begins the submition (Maps the vertex-&indexbuffer).
	void begin();

	// Submits the given vertices and indices into the render cache.
	void submit(const VertexPCT2D *vertices, GLuint vertexCount, const ELEMENT_INDEX_GL_TYPE *indices, GLuint indexCount, const Texture *texture = nullptr, float depth = 0.0f);

	// Submits the 4 given vertices into the render cache.
	void submit4(const VertexPCT2D *vertices, const Texture *texture = nullptr, float depth = 0.0f);

	// Submits the 16 given vertices into the render cache.
	void submit16(const VertexPCT2D *vertices, const Texture *texture = nullptr, float depth = 0.0f);

	// Submits the given text into the font render cache.
	//void submitText(const Text &text);

	// Submits the text part of given label into the font render chache.
	void submitLabel(const ui::Label &label);

	// Ends the submition (Unmaps the vertex-&indexbuffer).
	void end();

	// Takes all cached information and renders it.
	void flush();

	//const glm::vec2 &getOffset() const;
	//void setOffset(const glm::vec2 &offset);

	void pushScissor(GLint x, GLint y, GLint width, GLint height);
	void popScissor();

private:
	// Submits a texture into into the texuteSlots and returns the slot index.
	float submitTexture(const Texture *texture);

	// Submits a font atlas into the fontTextureSlots and returns the slot index.
	float submitFontAtlas(const Texture *texture);

	// Creates and sets the attribute locations of all buffers.
	void createBuffers();

	// Deletes all buffers.
	void deleteBuffers();

	// Sets the vertex data attribute locations for the currently bound vao.
	void setVertexDataAttribLocations();

	// vao, vertex data vbo, element index vbo
	GLuint dataBuffers[3];

	glm::vec2 offset;

	Shader *shader;
	Shader *fontShader;

	GLuint lightMap;

	//std::vector<const Text *> texts;
	std::vector<const ui::Label *> labels;
	//std::vector<unsigned int> sprites; // index count for each sprite
	//std::vector<Scissor> scissors;
	//std::vector<Scissor> textScissors;
	GLubyte scissorStackTop;
	Scissor scissorStack[Renderer2D::SCISSOR_STACK_SIZE];

	// mapped buffers
	VertexBuffer *vertexBuffer;
	ELEMENT_INDEX_GL_TYPE *indexBuffer;
	VertexBuffer *fontVertexBuffer;
	ELEMENT_INDEX_GL_TYPE *fontIndexBuffer;

	std::size_t vertexCount;
	std::size_t indexCount;

	std::size_t fontVertexCount;
	std::size_t fontIndexCount;

	GLubyte activeTextureSlotCount;
	GLuint textureSlots[Renderer2D::TEXTURE_SLOT_COUNT];

	GLubyte activeFontAtlasSlotCount;
	GLuint fontAtlasSlots[Renderer2D::TEXTURE_SLOT_COUNT];

	// TransformationStack (same for std and font)
	GLubyte transformationStackTop;
	glm::mat3 transformationStack[Renderer2D::TRANSFORMATION_STACK_SIZE];

	// Viewport information for position transforming
	GLint viewport[4];

	// Color used to clear the color buffer.
	glm::vec4 clearColor;

	GLuint fontUniformLocations[7];
};

// Inline

inline const glm::vec4 &Renderer2D::getClearColor() const
{
	return this->clearColor;
}

inline void Renderer2D::setClearColor(const glm::vec4 &clearColor)
{
	this->clearColor = clearColor;
}

inline void Renderer2D::setClearColor(float r, float g, float b, float a)
{
	this->clearColor.r = r;
	this->clearColor.g = g;
	this->clearColor.b = b;
	this->clearColor.a = a;
}

//inline const glm::vec2 &Renderer2D::getOffset() const
//{
//	return this->offset;
//}
//
//inline void Renderer2D::setOffset(const glm::vec2 &offset)
//{
//	this->offset = offset;
//}