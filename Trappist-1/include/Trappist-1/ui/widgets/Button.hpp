#pragma once

#include "Trappist-1\ui\widgets\Label.hpp"

namespace ui
{
	class Button : public Label
	{
		using BASE = Label;
	public:
		Button();

		virtual ~Button();

		// Returns the texture being rendered by default.
		const Texture *getDefaultTexture() const;

		// Sets the texture being rendered by default.
		void setDefaultTexture(const Texture *texture);

		// Returns the texture being rendered by default.
		const Texture *getPressedTexture() const;

		// Sets the texture being rendered if the button is pressed.
		void setPressedTexture(const Texture *texture);

		// Returns the texture being rendered by default.
		const Texture *getHighlightedTexture() const;

		// Sets the texture being rendered if the button is highlighted.
		void setHighlightedTexture(const Texture *texture);

		// Returns the texture being rendered by default.
		const Texture *getDisabledTexture() const;

		// Sets the texture being rendered if the button is disabled.
		void setDisabledTexture(const Texture *texture);

		// Returns the press offset.
		const glm::vec2 &getPressOffset() const;

		// Sets the press offset.
		void setPressOffset(const glm::vec2 &offset);

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		virtual void setPressed(bool pressed) override;
		virtual void setHighlighted(bool highlighted) override;
		virtual void setFocused(bool focused) override;
		virtual void setEnabledIH(bool enabled) override;

	private:
		const Texture *texDefault;
		const Texture *texPressed;
		const Texture *texHighlighted;
		const Texture *texDisabled;

		glm::vec2 pressOffset;
	};

	// Inline

	inline const Texture *Button::getDefaultTexture() const
	{
		return this->texDefault;
	}

	inline void Button::setDefaultTexture(const Texture *texture)
	{
		this->texDefault = texture;
	}

	inline const Texture *Button::getPressedTexture() const
	{
		return this->texPressed;
	}

	inline void Button::setPressedTexture(const Texture *texture)
	{
		this->texPressed = texture;
	}

	inline const Texture *Button::getHighlightedTexture() const
	{
		return this->texHighlighted;
	}

	inline void Button::setHighlightedTexture(const Texture *texture)
	{
		this->texHighlighted = texture;
	}

	inline const Texture *Button::getDisabledTexture() const
	{
		return this->texDisabled;
	}

	inline void Button::setDisabledTexture(const Texture *texture)
	{
		this->texDisabled = texture;
	}

	inline const glm::vec2 &Button::getPressOffset() const
	{
		return this->pressOffset;
	}

	inline void Button::setPressOffset(const glm::vec2 &offset)
	{
		this->pressOffset = offset;
	}
}