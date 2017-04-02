#include <Trappist-1\ui\widgets\Button.hpp>

namespace ui
{
	Button::Button()
		: BASE(), texDefault(nullptr), texPressed(nullptr), texHighlighted(nullptr), texDisabled(nullptr)
	{	}

	Button::~Button()
	{	}

	void Button::performSubmittion(Renderer2D &renderer2d) const
	{
		const_cast<Button*>(this)->translate(getPressOffset()); // TODO: find better fix
		BASE::performSubmittion(renderer2d);
		const_cast<Button*>(this)->translate(-getPressOffset()); // TODO: find better fix
	}

	void Button::setPressed(bool pressed)
	{
		BASE::setPressed(pressed);

		if (pressed && texPressed)
			setTexture(texPressed);
		else if (isHighlighted() && texHighlighted)
			setTexture(texHighlighted);
		else
			setTexture(texDefault);
	}

	void Button::setHighlighted(bool highlighted)
	{
		BASE::setHighlighted(highlighted);

		if (highlighted && texHighlighted)
			setTexture(texHighlighted);
		else
			setTexture(texDefault);
	}

	void Button::setFocused(bool focused)
	{
		BASE::setFocused(focused);
	}

	void Button::setEnabledIH(bool enabled)
	{
		BASE::setEnabled(enabled);

		if (!enabled && texDisabled)
			setTexture(texDisabled);
		else
			setTexture(texDefault);
		
	}
}