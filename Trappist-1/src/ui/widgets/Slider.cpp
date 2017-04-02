#include <Trappist-1\ui\widgets\Slider.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>
#include <Trappist-1\Util\Input.hpp>

namespace ui
{
	Slider::Slider()
		: BASE(), knobVertices(new VertexPCT2D[4]), texKnob(nullptr)
	{	}

	Slider::~Slider()
	{
		delete[] knobVertices;
	}

	void Slider::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);

		if (this->texKnob && this->texKnob->isSplit())
			renderer2d.submit16(knobVertices, texKnob);
		else
			renderer2d.submit4(knobVertices, texKnob);
	}

	glm::vec2 Slider::getKnobSize() const
	{
		if (this->texKnob && this->texKnob->isSplit())
			return knobVertices[15].position - knobVertices[0].position;
		else
			return knobVertices[2].position - knobVertices[0].position;
	}

	void Slider::setKnobSize(const glm::vec2 &size)
	{
		if (this->texKnob && this->texKnob->isSplit())
		{
			float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitLeft());
			float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitTop());
			float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitRight());
			float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitBottom());

			// Set x
			knobVertices[0].position.x = 0.0f;
			knobVertices[4].position.x = knobVertices[0].position.x;
			knobVertices[8].position.x = knobVertices[0].position.x;
			knobVertices[12].position.x = knobVertices[0].position.x;

			knobVertices[1].position.x = 0.0f + splitLeft;
			knobVertices[5].position.x = knobVertices[1].position.x;
			knobVertices[9].position.x = knobVertices[1].position.x;
			knobVertices[13].position.x = knobVertices[1].position.x;

			knobVertices[3].position.x = 0.0f + size.x;
			knobVertices[7].position.x = knobVertices[3].position.x;
			knobVertices[11].position.x = knobVertices[3].position.x;
			knobVertices[15].position.x = knobVertices[3].position.x;

			knobVertices[2].position.x = knobVertices[3].position.x - splitRight;
			knobVertices[6].position.x = knobVertices[2].position.x;
			knobVertices[10].position.x = knobVertices[2].position.x;
			knobVertices[14].position.x = knobVertices[2].position.x;

			// Set y
			knobVertices[0].position.y = 0.0f;
			knobVertices[1].position.y = knobVertices[0].position.y;
			knobVertices[2].position.y = knobVertices[0].position.y;
			knobVertices[3].position.y = knobVertices[0].position.y;

			knobVertices[4].position.y = 0.0f + splitTop;
			knobVertices[5].position.y = knobVertices[4].position.y;
			knobVertices[6].position.y = knobVertices[4].position.y;
			knobVertices[7].position.y = knobVertices[4].position.y;

			knobVertices[12].position.y = 0.0f + size.y;
			knobVertices[13].position.y = knobVertices[12].position.y;
			knobVertices[14].position.y = knobVertices[12].position.y;
			knobVertices[15].position.y = knobVertices[12].position.y;

			knobVertices[8].position.y = knobVertices[12].position.y - splitBottom;
			knobVertices[9].position.y = knobVertices[8].position.y;
			knobVertices[10].position.y = knobVertices[8].position.y;
			knobVertices[11].position.y = knobVertices[8].position.y;
		}
		else
		{
			knobVertices[0].position.x = 0.0f;
			knobVertices[0].position.y = 0.0f;

			knobVertices[1].position.x = 0.0f;
			knobVertices[1].position.y = size.y;

			knobVertices[2].position.x = size.x;
			knobVertices[2].position.y = size.y;

			knobVertices[3].position.x = size.x;
			knobVertices[3].position.y = 0.0f;
		}

		updateKnobPosition();
	}

	void Slider::setKnobColor(const glm::vec4 &progressColor)
	{
		knobVertices[0].color = progressColor;
		knobVertices[1].color = progressColor;
		knobVertices[2].color = progressColor;
		knobVertices[3].color = progressColor;

		if (texKnob && texKnob->isSplit())
		{
			knobVertices[4].color = progressColor;
			knobVertices[5].color = progressColor;
			knobVertices[6].color = progressColor;
			knobVertices[7].color = progressColor;
			knobVertices[8].color = progressColor;
			knobVertices[9].color = progressColor;
			knobVertices[10].color = progressColor;
			knobVertices[11].color = progressColor;
			knobVertices[12].color = progressColor;
			knobVertices[13].color = progressColor;
			knobVertices[14].color = progressColor;
			knobVertices[15].color = progressColor;
		}
	}

	void Slider::setKnobTexture(const Texture *texture)
	{
		if (texture)
		{
			bool changed = (this->texKnob && this->texKnob->isSplit()) != texture->isSplit();
			if (changed)
			{
				delete[] vertices;

				if (texture->isSplit())
					vertices = new VertexPCT2D[16];
				else
					vertices = new VertexPCT2D[4];
			}
		}
		this->texKnob = texture;
	}

	sf::FloatRect Slider::getKnobTextureRect() const
	{
		if (this->texKnob && this->texKnob->isSplit())
			return sf::FloatRect(knobVertices[0].texCoord.x, knobVertices[0].texCoord.y, knobVertices[15].texCoord.x - knobVertices[0].texCoord.x, knobVertices[15].texCoord.y - knobVertices[0].texCoord.y);
		else
			return sf::FloatRect(knobVertices[0].texCoord.x, knobVertices[0].texCoord.y, knobVertices[2].texCoord.x - knobVertices[0].texCoord.x, knobVertices[2].texCoord.y - knobVertices[0].texCoord.y);
	}

	void Slider::setKnobTextureRect(const sf::FloatRect &rect)
	{
		if (this->texKnob && this->texKnob->isSplit())
		{
			float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitLeft()) / static_cast<float>(texKnob->getSize().x);
			float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitTop()) / static_cast<float>(texKnob->getSize().y);
			float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitRight()) / static_cast<float>(texKnob->getSize().x);
			float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitBottom()) / static_cast<float>(texKnob->getSize().y);

			// Set x
			knobVertices[0].texCoord.x = rect.left;
			knobVertices[4].texCoord.x = knobVertices[0].texCoord.x;
			knobVertices[8].texCoord.x = knobVertices[0].texCoord.x;
			knobVertices[12].texCoord.x = knobVertices[0].texCoord.x;

			knobVertices[1].texCoord.x = rect.left + splitLeft;
			knobVertices[5].texCoord.x = knobVertices[1].texCoord.x;
			knobVertices[9].texCoord.x = knobVertices[1].texCoord.x;
			knobVertices[13].texCoord.x = knobVertices[1].texCoord.x;

			knobVertices[3].texCoord.x = rect.left + rect.width;
			knobVertices[7].texCoord.x = knobVertices[3].texCoord.x;
			knobVertices[11].texCoord.x = knobVertices[3].texCoord.x;
			knobVertices[15].texCoord.x = knobVertices[3].texCoord.x;

			knobVertices[2].texCoord.x = knobVertices[3].texCoord.x - splitRight;
			knobVertices[6].texCoord.x = knobVertices[2].texCoord.x;
			knobVertices[10].texCoord.x = knobVertices[2].texCoord.x;
			knobVertices[14].texCoord.x = knobVertices[2].texCoord.x;

			// Set y
			knobVertices[0].texCoord.y = rect.top;
			knobVertices[1].texCoord.y = knobVertices[0].texCoord.y;
			knobVertices[2].texCoord.y = knobVertices[0].texCoord.y;
			knobVertices[3].texCoord.y = knobVertices[0].texCoord.y;

			knobVertices[4].texCoord.y = rect.top + splitTop;
			knobVertices[5].texCoord.y = knobVertices[4].texCoord.y;
			knobVertices[6].texCoord.y = knobVertices[4].texCoord.y;
			knobVertices[7].texCoord.y = knobVertices[4].texCoord.y;

			knobVertices[12].texCoord.y = rect.top + rect.height;
			knobVertices[13].texCoord.y = knobVertices[12].texCoord.y;
			knobVertices[14].texCoord.y = knobVertices[12].texCoord.y;
			knobVertices[15].texCoord.y = knobVertices[12].texCoord.y;

			knobVertices[8].texCoord.y = knobVertices[12].texCoord.y - splitBottom;
			knobVertices[9].texCoord.y = knobVertices[8].texCoord.y;
			knobVertices[10].texCoord.y = knobVertices[8].texCoord.y;
			knobVertices[11].texCoord.y = knobVertices[8].texCoord.y;
		}
		else
		{
			knobVertices[0].texCoord.x = rect.left;
			knobVertices[0].texCoord.y = rect.top;

			knobVertices[1].texCoord.x = rect.left;
			knobVertices[1].texCoord.y = rect.top + rect.height;

			knobVertices[2].texCoord.x = rect.left + rect.width;
			knobVertices[2].texCoord.y = rect.top + rect.height;

			knobVertices[3].texCoord.x = rect.left + rect.width;
			knobVertices[3].texCoord.y = rect.top;
		}
	}

	void Slider::updateKnobPosition()
	{
		glm::vec2 knobSize = getKnobSize();
		glm::vec2 size = getSize();

		if (this->texKnob && this->texKnob->isSplit())
		{
			float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitLeft());
			float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitTop());
			float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitRight());
			float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texKnob)->getSplitBottom());

			// Set x
			knobVertices[0].position.x = glm::min((size.x - knobSize.x) * getProgress(), size.x - knobSize.x);
			knobVertices[4].position.x = knobVertices[0].position.x;
			knobVertices[8].position.x = knobVertices[0].position.x;
			knobVertices[12].position.x = knobVertices[0].position.x;

			knobVertices[1].position.x = knobVertices[0].position.x + splitLeft;
			knobVertices[5].position.x = knobVertices[1].position.x;
			knobVertices[9].position.x = knobVertices[1].position.x;
			knobVertices[13].position.x = knobVertices[1].position.x;

			knobVertices[3].position.x = knobVertices[0].position.x + knobSize.x;
			knobVertices[7].position.x = knobVertices[3].position.x;
			knobVertices[11].position.x = knobVertices[3].position.x;
			knobVertices[15].position.x = knobVertices[3].position.x;

			knobVertices[2].position.x = knobVertices[3].position.x - splitRight;
			knobVertices[6].position.x = knobVertices[2].position.x;
			knobVertices[10].position.x = knobVertices[2].position.x;
			knobVertices[14].position.x = knobVertices[2].position.x;

			// Set y
			knobVertices[0].position.y = 0.0f;
			knobVertices[1].position.y = knobVertices[0].position.y;
			knobVertices[2].position.y = knobVertices[0].position.y;
			knobVertices[3].position.y = knobVertices[0].position.y;

			knobVertices[4].position.y = 0.0f + splitTop;
			knobVertices[5].position.y = knobVertices[4].position.y;
			knobVertices[6].position.y = knobVertices[4].position.y;
			knobVertices[7].position.y = knobVertices[4].position.y;

			knobVertices[12].position.y = 0.0f + knobSize.y;
			knobVertices[13].position.y = knobVertices[12].position.y;
			knobVertices[14].position.y = knobVertices[12].position.y;
			knobVertices[15].position.y = knobVertices[12].position.y;

			knobVertices[8].position.y = knobVertices[12].position.y - splitBottom;
			knobVertices[9].position.y = knobVertices[8].position.y;
			knobVertices[10].position.y = knobVertices[8].position.y;
			knobVertices[11].position.y = knobVertices[8].position.y;
		}
		else
		{
			knobVertices[0].position.x = glm::min((size.x - knobSize.x) * getProgress(), size.x - knobSize.x);
			knobVertices[0].position.y = 0.0f;

			knobVertices[1].position.x = knobVertices[0].position.x;
			knobVertices[1].position.y = knobSize.y;

			knobVertices[2].position.x = knobVertices[0].position.x + knobSize.x;
			knobVertices[2].position.y = knobSize.y;

			knobVertices[3].position.x = knobVertices[0].position.x + knobSize.x;
			knobVertices[3].position.y = 0.0f;
		}
	}

	void Slider::onSizeChanged(const glm::vec2 &size)
	{
		BASE::onSizeChanged(size);
		updateKnobPosition();
	}

	void Slider::onProgressChanged()
	{
		updateKnobPosition();
	}

	void Slider::onMouseButtonEvent_decl
	{
		BASE::onMouseButtonEvent(button, pressed);

		if (isEnabled())
		{
			sf::FloatRect bounds = getGlobalBounds();
			glm::vec2 offset(Input::getMousePos().x - bounds.left, Input::getMousePos().y - bounds.top);
			setProgress((offset.x) / bounds.width);
		}
	}

	void Slider::onCursorPositionEvent_decl
	{
		BASE::onCursorPositionEvent();

		if (isEnabled() && isPressed())
		{
			sf::FloatRect bounds = getGlobalBounds();
			glm::vec2 offset(Input::getMousePos().x - bounds.left, Input::getMousePos().y - bounds.top);
			setProgress((offset.x) / bounds.width);
		}
	}

	void Slider::onMouseScrollWheelEvent_decl
	{
		BASE::onMouseScrollWheelEvent(offset);

		if (isEnabled())
		{
			addProgress(0.05f * offset.y);
		}
	}
}