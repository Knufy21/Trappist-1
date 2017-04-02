#include <Trappist-1\graphics\Texture.hpp>

#include <SFML\Graphics.hpp>

//namespace
//{
	Texture::Texture()
		: bools(0b0000'0001), handle(0)
	{  }

	Texture::Texture(const Texture &other)
		: bools(other.bools)
	{
		if (fileName)
			load(fileName);
	}

	Texture::Texture(Texture &&other)
		: bools(other.bools), fileName(other.fileName), handle(other.handle)
	{
	}

	Texture::~Texture()
	{
		unbind();

		if (glIsTexture(handle))
			glDeleteTextures(1, &handle);
	}

	Texture &Texture::operator=(const Texture &other)
	{
		bools = other.bools;

		if (fileName)
			load(fileName);

		return *this;
	}

	Texture &Texture::operator=(Texture &&other)
	{
		bools = other.bools;
		handle = other.handle;
		size = other.size;
		channels = other.channels;
		fileName = other.fileName;

		return *this;
	}

	bool Texture::load(const char *fileName)
	{
		if (fileName == nullptr)
			return false;

		if (glIsTexture(handle))
			glDeleteTextures(1, &handle);

		this->fileName = fileName;

		sf::Image img;
		if (!img.loadFromFile(fileName))
			return false;

		unsigned char *pixels = (unsigned char*)(img.getPixelsPtr());//ImageIO::loadFromFile(fileName, &width, &height, &channels);
		this->size.x = img.getSize().x;
		this->size.y = img.getSize().y;
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, isSmooth() ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, isSmooth() ? GL_LINEAR : GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);

		return true;
	}

	void Texture::unload()
	{
		if (glIsTexture(handle))
			glDeleteTextures(1, &handle);
	}

	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, handle);
	}

	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::setSmooth(bool smooth)
	{
		this->bools.set(Texture::BOOL_ARRAY_INDEX_SMOOTH, smooth);

		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST);
		unbind();
	}
//}