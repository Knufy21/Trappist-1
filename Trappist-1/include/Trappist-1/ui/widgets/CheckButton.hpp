#pragma once

#include "Trappist-1\ui\widgets\Image.hpp"

namespace ui
{
	class CheckButton : public Image
	{
		using BASE = Image;
		friend class CheckButtonGroup;
		friend class RadioButtonGroup;
	public:
		CheckButton();
		virtual ~CheckButton();

		void setChecked(bool checked);
		bool isChecked() const;

		void setCheckmarkTexture(const Texture &texture, bool resetCheckmarkSize);
		const Texture& getCheckmarkTexture() const;

		void setCheckmarkSize(const glm::vec2 &size);
		const glm::vec2 &getCheckmarkSize() const;

		void setCheckmarkColor(const glm::vec4 &color);
		const glm::vec4& getCheckmarkColor() const;

	protected:
		virtual void performSubmittion(Renderer2D &renderer2d) const override;

		//virtual void updatePosition() override;
		//virtual void onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f &mousePosRelTopLeft) override;
		//virtual void resetCheckmarkPosition();
		//virtual void updateCheckmarkPosition();

		bool checked;
		const Texture *texCheckmark;
		VertexPCT2D checkmarkVertices[4];
	private:
		CheckButtonGroup *checkButtonGroup;
	};
}