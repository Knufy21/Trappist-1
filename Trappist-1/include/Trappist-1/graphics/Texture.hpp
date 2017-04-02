#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>

#include <Trappist-1\util\EightBoolArray.hpp>

//namespace
//{
	class Texture
	{
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_SMOOTH	= 0;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_SPLIT		= 1;
	public:
		Texture();
		Texture(const Texture &other);
		Texture(Texture &&other);
		~Texture();

		Texture &operator=(const Texture &other);
		Texture &operator=(Texture &&other);

		// Loads the texture from the specified fileName path.
		bool load(const char *fileName);

		// Unloads the texture.
		void unload();

		// Binds the texture to be used in an OpenGL context.
		void bind() const;

		// Unbinds the texture.
		void unbind() const;

		// Sets whether the texture should be linearly interpolated or look pixelated.
		void setSmooth(bool smooth);

		// Returns the graphics api's texture handle.
		unsigned int getHandle() const;

		// Returns the size in pixles of the texture.
		const glm::ivec2 &getSize() const;

		// Returns whther the texture looks smooth or pixelated.
		bool isSmooth() const;

		// Returns whether the texture is split.
		bool isSplit() const;
	protected:
		void setSplit(bool split);

	private:
		EightBoolArray bools;
		GLuint handle;
		glm::ivec2 size;
		int channels;
		const char *fileName;
	};

	// Inline

	inline unsigned int Texture::getHandle() const
	{
		return this->handle;
	}

	inline const glm::ivec2 &Texture::getSize() const
	{
		return this->size;
	}

	inline bool Texture::isSmooth() const
	{
		return bools.get(Texture::BOOL_ARRAY_INDEX_SMOOTH);
	}

	inline bool Texture::isSplit() const
	{
		return bools.get(Texture::BOOL_ARRAY_INDEX_SPLIT);
	}

	inline void Texture::setSplit(bool split)
	{
		this->bools.set(Texture::BOOL_ARRAY_INDEX_SPLIT, split);
	}
//}