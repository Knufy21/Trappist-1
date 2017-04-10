#pragma once

#include <vector>
#include <memory>
#include <algorithm>

#include <Trappist-1\graphics\Rect.hpp>
#include <Trappist-1\graphics\Transform2D.hpp>
#include <Trappist-1\graphics\Vertex2D.hpp>
#include <Trappist-1\graphics\Texture.hpp>
#include <Trappist-1\Graphics\SplitTexture.hpp>

#include <Trappist-1\util\EightBoolArray.hpp>

#include "Trappist-1\ui\listeners\Listener.hpp"

class Renderer2D;
namespace ui
{
	class Action;
	// The base class for all gui stuff.
	class Widget : public Transform2D
	{
		using BASE = Transform2D;

		friend class Screen;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_VISIBLE			=	0;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_EVENT_RECEIVER	=	1;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_PRESSED			=	2;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_HIGHLIGHTED		=	3;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_FOCUSED			=	4;
		static constexpr EightBoolArray::value_t BOOL_ARRAY_INDEX_ENABLED			=	5;
	public:
		Widget();

		virtual ~Widget();

		// Submits the widget to a renderer.
		void submit(::Renderer2D &renderer2d) const;

		// Updates the widget.
		void update(float deltaTime);

		// Adds a copy of the action to the widget.
		void addAction(Action &action);

		// Removes an action of the widget.
		void removeAction(Action &action);

		// Returns the parent of the widget. If the widget does not have a parent, nullptr is being returned.
		const Widget *getParent() const;

		// Sets the parent of the widget. To remove the widgets parent, nullptr can be passed in.
		void setParent(const Widget *parent);

		// Returns the size of the widget measured in pixels.
		const glm::vec2 &getSize() const;

		// Sets the size of the widget measured in pixels.
		void setSize(const glm::vec2 &size);

		// Sets the size of the widget measured in pixels.
		void setSize(float width, float height);

		// Returns the color of the widget.
		const glm::vec4 &getColor() const;

		// Sets the color of the widget.
		void setColor(const glm::vec4 &color);

		// Sets the color of the widget. (new, not implemented)
		//void setColor(const sf::Color &color);

		// Returns the local bounds of the widget, which have no transformations applied.
		FloatRect getLocalBounds() const;

		// Returns the global bounds of the widget, which have all transformations applied.
		FloatRect getGlobalBounds() const;

		// Returns the visibility of the widget.
		bool isVisible() const;

		// Sets the visibility of the widget.
		void setVisible(bool visible);

		// Returns the texture of the image being used for rendering.
		const Texture *getTexture() const;

		// Sets the texture of the image being used for rendering.
		void setTexture(const Texture *texture, bool resetTexCoords = true);

		// Returns the texture rect of all vertices measured by a value between 0 and 1.
		FloatRect getTextureRect() const;

		// Sets the texture rect for all vertices measured in pixels.
		void setTextureRect(const IntRect &rect);

		// Sets the texture rect for all vertices measured by a value between 0 and 1.
		void setTextureRect(const FloatRect &rect);

		// CONTROL

		// Returns whether the widget can receive events or not.
		bool isEventReceiver() const;

		// Sets whether the widget can receive events or not.
		void setEventReceiver(bool eventReceiver);

		// Adds the specified listener into the listeners list.
		void addListener(Listener &listener);

		// Sets the only one child of the control.
		void setChild(Widget *child);

		// Returns the only one child of the control.
		const Widget *getChild() const;

		// Sets the enabled value of the control, which determines if it can receive events.
		void setEnabled(bool enabled);

		// Returns whether the control is pressed or not.
		bool isPressed() const;

		// Returns whether the control is highlighted or not.
		bool isHighlighted() const;

		// Returns whether the control is focused or not.
		bool isFocused() const;

		// Returns whether the control is enabled or not.
		bool isEnabled() const;

	protected:
		// Begins the submission by pushing the transform matrix onto the renderer.
		virtual void beginSubmission(::Renderer2D &renderer2d) const;

		// Performs the submittion by submitting the vertices to the renderer.
		virtual void performSubmittion(::Renderer2D &renderer2d) const;

		// Ends the submission by popping the transform matrix from the renderer.
		virtual void endSubmission(::Renderer2D &renderer2d) const;

		// Event which is fired when the size of the widget has been modified.
		virtual void onSizeChanged(const glm::vec2 &size);

		// Sets whether the control is pressed or not.
		virtual void setPressed(bool pressed);

		// Sets whether the control is highlighted or not.
		virtual void setHighlighted(bool highlighted);

		// Sets whether the control is focused or not.
		virtual void setFocused(bool focused);

		// Sets the enabled value of the control, which determines if it can receive events (for inheratance).
		virtual void setEnabledIH(bool enabled);

		#define onMouseButtonEvent_decl			onMouseButtonEvent(sf::Mouse::Button button, bool pressed)
		#define onCursorPositionEvent_decl		onCursorPositionEvent()
		#define onCursorEnterEvent_decl			onCursorEnterEvent(bool entered)
		#define onMouseScrollWheelEvent_decl	onMouseScrollWheelEvent(const glm::vec2 &offset)
		#define onFocusEvent_decl				onFocusEvent(bool focused)
		#define onKeyEvent_decl					onKeyEvent(sf::Keyboard::Key key, bool pressed, bool alt, bool control, bool shift, bool system)
		#define onCharEvent_decl				onCharEvent(unsigned int codepoint)

		virtual void onMouseButtonEvent_decl;
		virtual void onCursorPositionEvent_decl;
		virtual void onCursorEnterEvent_decl;
		virtual void onMouseScrollWheelEvent_decl;
		virtual void onFocusEvent_decl;
		virtual void onKeyEvent_decl;
		virtual void onCharEvent_decl;

		//virtual void onMouseButtonEvent(sf::Mouse::Button button, bool pressed);
		//virtual void onCursorPositionEvent();
		//virtual void onCursorEnterEvent(bool entered);
		//virtual void onMouseScrollWheelEvent(const glm::vec2 &offset);
		//virtual void onFocusEvent(bool focused);
		//virtual void onKeyEvent(sf::Keyboard::Key key, bool pressed, bool alt, bool control, bool shift, bool system);
		//virtual void onCharEvent(unsigned int codepoint);

		// Not available with SFML.
		virtual void onDropEvent(unsigned int fileCount, const char **filePaths);

		// °0  °3 --- °0  °3
		// °1  °2 --- °12 °15
		VertexPCT2D *vertices;
	private:

		// The texture of the Image being used for rendering.
		const Texture *texture;

		// The actions vector contains all actions that are being requested or executing.
		std::vector<Action*> actions;

		// The parent of the widget.
		const Widget *parent;

		// CONTROL

		// The only one child of the control.
		Widget *child;

		// An array of bool which are pressed, highlighted, focused, enabled
		EightBoolArray boolArray;

		// A vector of listeners.
		std::vector<std::unique_ptr<Listener>> listeners;
	};

	// Inline

	inline bool Widget::isVisible() const
	{
		return this->boolArray.get(Widget::BOOL_ARRAY_INDEX_VISIBLE);
	}

	inline void Widget::setVisible(bool visible)
	{
		this->boolArray.set(Widget::BOOL_ARRAY_INDEX_VISIBLE, visible);
	}

	inline const Texture *Widget::getTexture() const
	{
		return this->texture;
	}

	inline const glm::vec4 &Widget::getColor() const
	{
		return vertices[0].color;
	}

	// CONTROL

	inline bool Widget::isEventReceiver() const
	{
		return this->boolArray.get(Widget::BOOL_ARRAY_INDEX_EVENT_RECEIVER);
	}

	inline void Widget::setEventReceiver(bool eventReceiver)
	{
		this->boolArray.set(Widget::BOOL_ARRAY_INDEX_EVENT_RECEIVER, eventReceiver);
	}

	inline bool Widget::isPressed() const
	{
		return this->boolArray.get(Widget::BOOL_ARRAY_INDEX_PRESSED);
	}

	inline bool Widget::isHighlighted() const
	{
		return this->boolArray.get(Widget::BOOL_ARRAY_INDEX_HIGHLIGHTED);
	}

	inline bool Widget::isFocused() const
	{
		return this->boolArray.get(Widget::BOOL_ARRAY_INDEX_FOCUSED);
	}

	inline bool Widget::isEnabled() const
	{
		return this->boolArray.get(Widget::BOOL_ARRAY_INDEX_ENABLED);
	}

	inline const Widget *Widget::getChild() const
	{
		return this->child;
	}
}