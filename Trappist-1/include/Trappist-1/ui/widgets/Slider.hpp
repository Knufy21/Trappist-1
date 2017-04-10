#pragma once

#include "Trappist-1\ui\widgets\Progressbar.hpp"

namespace ui
{
	class Slider : public Progressbar
	{
		using BASE = Progressbar;
	public:
		Slider();

		virtual ~Slider();

		// Returns the size of the knob.
		glm::vec2 getKnobSize() const;

		// Sets the size of the knob.
		void setKnobSize(const glm::vec2 &size);

		// Returns the color of the progress.
		const glm::vec4 &getKnobColor() const;

		// Sets the color of the progress.
		void setKnobColor(const glm::vec4 &progressColor);

		// Returns the texture used to render the progress.
		const Texture *getKnobTexture() const;

		// Sets the texture used to render the progress.
		void setKnobTexture(const Texture *texture);

		// Returns the texture rect for all vertices measured by a value between 0 and 1.
		FloatRect getKnobTextureRect() const;

		// Sets the texture rect for all vertices measured by a value between 0 and 1.
		void setKnobTextureRect(const FloatRect &rect);

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		virtual void onSizeChanged(const glm::vec2 &size) override;

		virtual void onProgressChanged() override;

		virtual void onMouseButtonEvent_decl override;
		virtual void onCursorPositionEvent_decl override;
		virtual void onMouseScrollWheelEvent_decl override;

	private:
		void updateKnobPosition();

		VertexPCT2D *knobVertices;
		const Texture *texKnob;
	};

	// Inline

	inline const glm::vec4 &Slider::getKnobColor() const
	{
		return knobVertices[0].color;
	}

	inline const Texture *Slider::getKnobTexture() const
	{
		return this->texKnob;
	}
}