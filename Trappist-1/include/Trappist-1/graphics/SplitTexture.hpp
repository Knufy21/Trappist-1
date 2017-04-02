#pragma once

#include <Trappist-1\graphics\Texture.hpp>

//namespace
//{
	class SplitTexture : public Texture
	{
	public:
		SplitTexture(unsigned short splitLeft, unsigned short splitTop, unsigned short splitRight, unsigned short splitBottom);

		// Returns the position of the split from the left side of the texture in pixels.
		unsigned short getSplitLeft() const;

		// Returns the position of the split from the top side of the texture in pixels.
		unsigned short getSplitTop() const;

		// Returns the position of the split from the right side of the texture in pixels.
		unsigned short getSplitRight() const;

		// Returns the position of the split from the bottom side of the texture in pixels.
		unsigned short getSplitBottom() const;

	private:
		const unsigned short splitLeft;
		const unsigned short splitTop;
		const unsigned short splitRight;
		const unsigned short splitBottom;
	};

	// Inline

	inline SplitTexture::SplitTexture(unsigned short splitLeft, unsigned short splitTop, unsigned short splitRight, unsigned short splitBottom)
		: Texture(), splitLeft(splitLeft), splitTop(splitTop), splitRight(splitRight), splitBottom(splitBottom)
	{
		setSplit(true);
	}

	inline unsigned short SplitTexture::getSplitLeft() const
	{
		return this->splitLeft;
	}

	inline unsigned short SplitTexture::getSplitTop() const
	{
		return this->splitTop;
	}

	inline unsigned short SplitTexture::getSplitRight() const
	{
		return this->splitRight;
	}

	inline unsigned short SplitTexture::getSplitBottom() const
	{
		return this->splitBottom;
	}
//}