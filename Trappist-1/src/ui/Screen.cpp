#include <Trappist-1\ui\Screen.hpp>

#include <Trappist-1\graphics\Renderer2D.hpp>
#include <Trappist-1\ui\widgets\Widget.hpp>

namespace ui
{
	Screen::Screen()
	{	}

	Screen::~Screen()
	{	}

	void Screen::submit(Renderer2D &renderer2d)
	{
		for (auto it = this->widgets.begin(); it != this->widgets.end(); ++it)
			(*it)->submit(renderer2d);
	}

	void Screen::update(float deltaTime)
	{
		for (auto it = this->widgets.begin(); it != this->widgets.end(); ++it)
			(*it)->update(deltaTime);
	}

	void Screen::handle(sf::Window &window, sf::Event &event)
	{
		switch (event.type)
		{
		case sf::Event::Resized:
			if(this->sizeChangedFun)
				this->sizeChangedFun(event.size.width, event.size.height);
			break;
		case sf::Event::MouseButtonPressed:
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{
					
					if (widget->getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
					{
						widget->onMouseButtonEvent(event.mouseButton.button, true);
						if (!widget->isFocused())
							widget->onFocusEvent(true);
					}
					else
					{
						if (widget->isFocused()/* && control->focusable*/)
							widget->onFocusEvent(false);
					}
				}
			}
			break;
		case sf::Event::MouseButtonReleased:
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{

					if (widget->getGlobalBounds().contains(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)))
					{
						widget->onMouseButtonEvent(event.mouseButton.button, false);
						if (!widget->isFocused())
							widget->onFocusEvent(true);
					}
					else
					{
						if (widget->isFocused()/* && control->focusable*/)
							widget->onFocusEvent(false);
					}
				}
			}
			break;
		case sf::Event::MouseMoved:
			this->mousePosition.x = event.mouseMove.x;
			this->mousePosition.y = event.mouseMove.y;
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{
					if (widget->getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))
					{
						widget->onCursorPositionEvent();
						if (!widget->isHighlighted())
							widget->onCursorEnterEvent(true);
					}
					else
					{
						if (widget->isHighlighted())
							widget->onCursorEnterEvent(false);
					}
				}
			}
			break;
		case sf::Event::MouseWheelScrolled:
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{
					if (widget->isFocused() || widget->getGlobalBounds().contains(static_cast<float>(event.mouseWheelScroll.x), static_cast<float>(event.mouseWheelScroll.y)))
						widget->onMouseScrollWheelEvent(glm::vec2(static_cast<float>(event.mouseWheelScroll.delta), static_cast<float>(event.mouseWheelScroll.delta)));
				}
			}
			break;
		case sf::Event::KeyPressed:
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{
					if (widget->isFocused() || widget->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
						widget->onKeyEvent(event.key.code, true, event.key.alt, event.key.control, event.key.shift, event.key.system);
				}
			}
			break;
		case sf::Event::KeyReleased:
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{
					if (widget->isFocused() || widget->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
						widget->onKeyEvent(event.key.code, false, event.key.alt, event.key.control, event.key.shift, event.key.system);
				}
			}
			break;
		case sf::Event::TextEntered:
			for (Widget *widget : this->widgets)
			{
				if (widget->isEventReceiver())
				{
					
					if (widget->isFocused() || widget->getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
						widget->onCharEvent(event.text.unicode);
				}
			}
			break;
		}	
	}
}