#pragma once

#include <functional>
#include <unordered_set>
#include <list>
#include <glm\glm.hpp>
#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>

class Renderer2D;
namespace ui
{
	class Widget;
	class Screen
	{
	public:
		Screen();
		virtual ~Screen();

		// Updates all widgets with the speicifed deltaTime.
		void update(float deltaTime);

		// Handles an event created by the specified window.
		void handle(sf::Window &window, sf::Event &event);

		// Adds the specified widget to the screen.
		void addWidget(Widget *widget);

		// Removes the specified widget to the screen.
		void removeWidget(Widget *widget);

		// Schedules an event being called when the specified time in seconds has past.
		void scheduleEvent(float time, std::function<void()> onEvent);

		// Event being called when the size of the window has been changed.
		virtual void onSizeChanged(unsigned int width, unsigned int height);
	private:
		std::list<std::pair<float, std::function<void()>>> scheduledEvents;
		std::unordered_set<Widget *> widgets;
		glm::ivec2 mousePosition;
	};

	// Inline

	inline void Screen::addWidget(Widget *widget)
	{
		this->widgets.insert(widget);
	}

	inline void Screen::removeWidget(Widget *widget)
	{
		this->widgets.erase(widget);
	}
}