#include <Trappist-1\ui\widgets\Widget.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>
#include <Trappist-1\ui\actions\Action.hpp>

#define WIDGET_DEFAULT_VISIBILITY			true
#define WIDGET_DEFAULT_PARENT				nullptr
#define WIDGET_DEFAULT_SPLIT				false
#define WIDGET_DEFAULT_TEXTURE				nullptr
#define WIDGET_DEFAULT_CHILD				nullptr
#define WIDGET_DEFAULT_BOOL_ARRAY_VALUE		0b0010'0001

namespace ui
{
	Widget::Widget()
		: parent(WIDGET_DEFAULT_PARENT), texture(WIDGET_DEFAULT_TEXTURE), boolArray(WIDGET_DEFAULT_BOOL_ARRAY_VALUE), child(WIDGET_DEFAULT_CHILD)
	{
		vertices = new VertexPCT2D[4];
		setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	}

	Widget::~Widget()
	{	}

	void Widget::submit(Renderer2D &renderer2d) const
	{
		if (isVisible())
		{
			beginSubmission(renderer2d);
			performSubmittion(renderer2d);
			endSubmission(renderer2d);
		}
	}

	void Widget::update(float deltaTime)
	{
		for (size_t i = 0; i < actions.size(); ++i)
		{
			actions[i]->update(deltaTime);
			if (actions[i]->hasFinished())
				removeAction(*(actions[i]));
		}
	}

	void Widget::addAction(Action &action)
	{
		Action *ptrAction = action.clone();
		ptrAction->setTarget(*this);
		//ptrAction->setFinishListener([this, ptrAction]() { this->removeAction(*ptrAction); });
		actions.emplace_back(ptrAction);
	}

	void Widget::removeAction(Action &action)
	{
		actions.erase(std::remove(actions.begin(), actions.end(), &action), actions.end());
		delete &action;
	}

	const Widget *Widget::getParent() const
	{
		return parent;
	}

	void Widget::setParent(const Widget *parent)
	{
		this->parent = parent;
	}

	const glm::vec2 &Widget::getSize() const
	{
		if(this->texture && this->texture->isSplit())
			return vertices[15].position;
		else
			return vertices[2].position;
	}

	void Widget::setSize(const glm::vec2 &size)
	{
		setSize(size.x, size.y);
	}

	void Widget::setSize(float width, float height)
	{
		if (this->texture && this->texture->isSplit())
		{
			float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitLeft());
			float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitTop());
			float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitRight());
			float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitBottom());

			// Set x
			vertices[0].position.x = 0.0f;
			vertices[4].position.x = vertices[0].position.x;
			vertices[8].position.x = vertices[0].position.x;
			vertices[12].position.x = vertices[0].position.x;

			vertices[1].position.x = 0.0f + splitLeft;
			vertices[5].position.x = vertices[1].position.x;
			vertices[9].position.x = vertices[1].position.x;
			vertices[13].position.x = vertices[1].position.x;

			vertices[3].position.x = 0.0f + width;
			vertices[7].position.x = vertices[3].position.x;
			vertices[11].position.x = vertices[3].position.x;
			vertices[15].position.x = vertices[3].position.x;

			vertices[2].position.x = vertices[3].position.x - splitRight;
			vertices[6].position.x = vertices[2].position.x;
			vertices[10].position.x = vertices[2].position.x;
			vertices[14].position.x = vertices[2].position.x;

			// Set y
			vertices[0].position.y = 0.0f;
			vertices[1].position.y = vertices[0].position.y;
			vertices[2].position.y = vertices[0].position.y;
			vertices[3].position.y = vertices[0].position.y;

			vertices[4].position.y = 0.0f + splitTop;
			vertices[5].position.y = vertices[4].position.y;
			vertices[6].position.y = vertices[4].position.y;
			vertices[7].position.y = vertices[4].position.y;

			vertices[12].position.y = 0.0f + height;
			vertices[13].position.y = vertices[12].position.y;
			vertices[14].position.y = vertices[12].position.y;
			vertices[15].position.y = vertices[12].position.y;

			vertices[8].position.y = vertices[12].position.y - splitBottom;
			vertices[9].position.y = vertices[8].position.y;
			vertices[10].position.y = vertices[8].position.y;
			vertices[11].position.y = vertices[8].position.y;
		}
		else
		{
			vertices[1].position.y = height;

			vertices[2].position.x = width;
			vertices[2].position.y = height;

			vertices[3].position.x = width;
		}

		onSizeChanged(glm::vec2(width, height)); // TODO: optimize (no vec2 creation)
	}

	void Widget::setColor(const glm::vec4 &color)
	{
		vertices[0].color = color;
		vertices[1].color = color;
		vertices[2].color = color;
		vertices[3].color = color;

		if (this->texture && this->texture->isSplit())
		{
			vertices[4].color = color;
			vertices[5].color = color;
			vertices[6].color = color;
			vertices[7].color = color;
			vertices[8].color = color;
			vertices[9].color = color;
			vertices[10].color = color;
			vertices[11].color = color;
			vertices[12].color = color;
			vertices[13].color = color;
			vertices[14].color = color;
			vertices[15].color = color;
		}
	}

	//void Widget::setColor(const sf::Color &color)
	//{
		//vertices[0].color = color;
		//vertices[1].color = color;
		//vertices[2].color = color;
		//vertices[3].color = color;
		//
		//if (this->texture && this->texture->isSplit())
		//{
		//	vertices[4].color = color;
		//	vertices[5].color = color;
		//	vertices[6].color = color;
		//	vertices[7].color = color;
		//	vertices[8].color = color;
		//	vertices[9].color = color;
		//	vertices[10].color = color;
		//	vertices[11].color = color;
		//	vertices[12].color = color;
		//	vertices[13].color = color;
		//	vertices[14].color = color;
		//	vertices[15].color = color;
		//}
	//}

	FloatRect Widget::getLocalBounds() const
	{
		if(this->texture && this->texture->isSplit())
			return FloatRect(0.0f, 0.0f, vertices[15].position.x, vertices[15].position.y);
		else
			return FloatRect(0.0f, 0.0f, vertices[2].position.x, vertices[2].position.y);
	}

	FloatRect Widget::getGlobalBounds() const
	{
		return transformRect(getLocalBounds());
	}

	void Widget::setTexture(const Texture *texture, bool resetTexCoords)
	{
		if (texture)
		{
			bool changed = (this->texture && this->texture->isSplit()) != texture->isSplit();
			if (changed)
			{
				delete[] vertices;

				if (texture->isSplit())
					vertices = new VertexPCT2D[16];
				else
					vertices = new VertexPCT2D[4];
			}
		}
		this->texture = texture;

		if (resetTexCoords)
			setTextureRect(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
	}

	FloatRect Widget::getTextureRect() const
	{
		if (this->texture && this->texture->isSplit())
			return FloatRect(vertices[0].texCoord.x, vertices[0].texCoord.y, vertices[15].texCoord.x - vertices[0].texCoord.x, vertices[15].texCoord.y - vertices[0].texCoord.y);
		return FloatRect(vertices[0].texCoord.x, vertices[0].texCoord.y, vertices[2].texCoord.x - vertices[0].texCoord.x, vertices[2].texCoord.y - vertices[0].texCoord.y);
	}

	void Widget::setTextureRect(const IntRect &rect)
	{
		setTextureRect(FloatRect(
			static_cast<float>(rect.left) / static_cast<float>(texture->getSize().x),
			static_cast<float>(rect.top) / static_cast<float>(texture->getSize().y),
			static_cast<float>(rect.width) / static_cast<float>(texture->getSize().x),
			static_cast<float>(rect.height) / static_cast<float>(texture->getSize().y)));
	}

	void Widget::setTextureRect(const FloatRect &rect)
	{
		if (this->texture && this->texture->isSplit())
		{
			float splitLeft = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitLeft()) / static_cast<float>(texture->getSize().x);
			float splitTop = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitTop()) / static_cast<float>(texture->getSize().y);
			float splitRight = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitRight()) / static_cast<float>(texture->getSize().x);
			float splitBottom = static_cast<float>(static_cast<const SplitTexture*>(texture)->getSplitBottom()) / static_cast<float>(texture->getSize().y);

			// Set x
			vertices[0].texCoord.x = rect.left;
			vertices[4].texCoord.x = vertices[0].texCoord.x;
			vertices[8].texCoord.x = vertices[0].texCoord.x;
			vertices[12].texCoord.x = vertices[0].texCoord.x;

			vertices[1].texCoord.x = rect.left + splitLeft;
			vertices[5].texCoord.x = vertices[1].texCoord.x;
			vertices[9].texCoord.x = vertices[1].texCoord.x;
			vertices[13].texCoord.x = vertices[1].texCoord.x;

			vertices[3].texCoord.x = rect.left + rect.width;
			vertices[7].texCoord.x = vertices[3].texCoord.x;
			vertices[11].texCoord.x = vertices[3].texCoord.x;
			vertices[15].texCoord.x = vertices[3].texCoord.x;

			 vertices[2].texCoord.x = vertices[3].texCoord.x - splitRight;
			 vertices[6].texCoord.x = vertices[2].texCoord.x;
			 vertices[10].texCoord.x = vertices[2].texCoord.x;
			 vertices[14].texCoord.x = vertices[2].texCoord.x;

			// Set y
			vertices[0].texCoord.y = rect.top;
			vertices[1].texCoord.y = vertices[0].texCoord.y;
			vertices[2].texCoord.y = vertices[0].texCoord.y;
			vertices[3].texCoord.y = vertices[0].texCoord.y;

			vertices[4].texCoord.y = rect.top + splitTop;
			vertices[5].texCoord.y = vertices[4].texCoord.y;
			vertices[6].texCoord.y = vertices[4].texCoord.y;
			vertices[7].texCoord.y = vertices[4].texCoord.y;

			vertices[12].texCoord.y = rect.top + rect.height;
			vertices[13].texCoord.y = vertices[12].texCoord.y;
			vertices[14].texCoord.y = vertices[12].texCoord.y;
			vertices[15].texCoord.y = vertices[12].texCoord.y;

			 vertices[8].texCoord.y = vertices[12].texCoord.y - splitBottom;
			 vertices[9].texCoord.y = vertices[8].texCoord.y;
			 vertices[10].texCoord.y = vertices[8].texCoord.y;
			 vertices[11].texCoord.y = vertices[8].texCoord.y;
		}
		else
		{
			vertices[0].texCoord.x = rect.left;
			vertices[0].texCoord.y = rect.top;

			vertices[1].texCoord.x = rect.left;
			vertices[1].texCoord.y = rect.top + rect.height;

			vertices[2].texCoord.x = rect.left + rect.width;
			vertices[2].texCoord.y = rect.top + rect.height;

			vertices[3].texCoord.x = rect.left + rect.width;
			vertices[3].texCoord.y = rect.top;
		}
	}

	void Widget::beginSubmission(Renderer2D &renderer2d) const
	{
		renderer2d.pushMatrix(getTransform());
	}

	void Widget::performSubmittion(Renderer2D &renderer2d) const
	{
		if(this->texture && this->texture->isSplit())
			renderer2d.submit16(vertices, texture);
		else
			renderer2d.submit4(vertices, texture);

		// Control
		if (child)
			child->submit(renderer2d);
	}

	void Widget::endSubmission(Renderer2D &renderer2d) const
	{
		renderer2d.popMatrix();
	}

	void Widget::onSizeChanged(const glm::vec2 &size)
	{

	}

	// CONTROL

	void Widget::addListener(Listener &listener)
	{
		listeners.emplace_back(std::make_unique<Listener>(listener));
	}

	void Widget::setChild(Widget *child)
	{
		if (child != nullptr)
			child->setParent(this);
		this->child = child;
	}

	void Widget::setEnabled(bool enabled)
	{
		setEnabledIH(enabled);
	}

	void Widget::setPressed(bool pressed)
	{
		boolArray.set(Widget::BOOL_ARRAY_INDEX_PRESSED, pressed);
	}

	void Widget::setHighlighted(bool highlighted)
	{
		boolArray.set(Widget::BOOL_ARRAY_INDEX_HIGHLIGHTED, highlighted);
	}

	void Widget::setFocused(bool focused)
	{
		boolArray.set(Widget::BOOL_ARRAY_INDEX_FOCUSED, focused);
	}

	void Widget::setEnabledIH(bool enabled)
	{
		boolArray.set(Widget::BOOL_ARRAY_INDEX_ENABLED, enabled);

		if (!enabled)
		{
			setPressed(false);
			setHighlighted(false);
			setFocused(false);
		}
	}

	// Events

	void Widget::onMouseButtonEvent(sf::Mouse::Button button, bool pressed)
	{
		if (isEnabled())
		{
			setPressed(pressed);

			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::MOUSE_BUTTON_EVENT)
				{
					MouseButtonEventArgs args{ button, pressed };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onCursorPositionEvent()
	{
		if (isEnabled())
		{
			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::CURSOR_POSITION_EVENT)
				{
					CursorPositionEventArgs args{};
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onCursorEnterEvent(bool entered)
	{
		if (isEnabled())
		{
			setHighlighted(entered);

			if (!entered && isPressed())
				setPressed(false);

			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::CURSOR_ENTER_EVENT)
				{
					CursorEnterEventArgs args{ entered };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onMouseScrollWheelEvent(const glm::vec2 &offset)
	{
		if (isEnabled())
		{
			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::MOUSE_SCROLL_WHEEL_EVENT)
				{
					MouseScrollWheelEventArgs args{ offset };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onFocusEvent(bool focused)
	{
		if (isEnabled())
		{
			setFocused(focused);

			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::FOCUS_EVENT)
				{
					FocusEventArgs args{ focused };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onKeyEvent(sf::Keyboard::Key key, bool pressed, bool alt, bool control, bool shift, bool system)
	{
		if (isEnabled())
		{
			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::KEY_EVENT)
				{
					KeyEventArgs args{ key, pressed, alt, control, shift, system };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onCharEvent(unsigned int codepoint)
	{
		if (isEnabled())
		{
			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::CHAR_EVENT)
				{
					CharEventArgs args{ codepoint };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}

	void Widget::onDropEvent(unsigned int fileCount, const char **filePaths)
	{
		if (isEnabled())
		{
			for (unsigned int i = 0; i < listeners.size(); ++i)
			{
				if (listeners[i]->getType() == Listener::Type::DROP_EVENT)
				{
					DropEventArgs args{ fileCount, filePaths };
					listeners[i]->fireEvent(static_cast<const void *>(&args));
				}
			}
		}
	}
}