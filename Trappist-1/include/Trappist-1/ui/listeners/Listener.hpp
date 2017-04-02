#pragma once

#include <functional>

#include "glm\glm.hpp"

#include <SFML\Graphics.hpp>

namespace ui
{
	struct MouseButtonEventArgs
	{
		sf::Mouse::Button button;
		bool pressed;
	};

	struct CursorPositionEventArgs
	{
	};

	struct CursorEnterEventArgs
	{
		bool entered;
	};

	struct MouseScrollWheelEventArgs
	{
		// The horizontal offset x of the scroll wheel (right: + | left: -).
		// The vertical offset y of the scroll wheel (up: + | down: -).
		glm::vec2 offset;
	};

	struct FocusEventArgs
	{
		bool focused;
	};
	
	struct KeyEventArgs
	{
		sf::Keyboard::Key key;
		bool pressed;
		bool alt;
		bool control;
		bool shift;
		bool system;
	};

	// The CharModsEvent is fired when a character has been typed on the keyboard.
	struct CharEventArgs
	{
		unsigned int codepoint; // The Unicode codepoint of the character that has been typed.
		//Keyboard::Mod mods;		// 
	};

	// The DropEvent is fired when one or more files have been dropped into the window.
	struct DropEventArgs
	{
		unsigned int count;	// The number of files which have been dropped.
		const char **paths; // The paths to the files which have been dropped.
	};

	class Listener
	{
	public:
		enum class Type { MOUSE_BUTTON_EVENT, CURSOR_POSITION_EVENT, CURSOR_ENTER_EVENT, MOUSE_SCROLL_WHEEL_EVENT, FOCUS_EVENT, KEY_EVENT, CHAR_EVENT, DROP_EVENT, COUNT };

		inline void fireEvent(const void *eventArgs) { onListenerEvent(eventArgs); }
		inline Type getType() const { return type; }

	protected:
		Listener(Type type, std::function<void(const void *)> onListenerEvent) : type(type), onListenerEvent(onListenerEvent) {	}
	private:
		Type type;
		std::function<void(const void *)> onListenerEvent;
	};
}