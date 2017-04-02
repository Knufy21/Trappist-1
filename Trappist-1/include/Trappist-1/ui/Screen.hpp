#pragma once

#include <functional>
#include <unordered_set>
#include <SFML\Graphics.hpp>
#include <glm\glm.hpp>

class Renderer2D;
namespace ui
{
	class Widget;
	//class Window;
	//struct Event;
	class Screen
	{
	public:
		Screen();
		virtual ~Screen();

		// Submits all widgets to the specified renderer.
		void submit(Renderer2D &renderer2d);

		// Updates all widgets with the speicifed deltaTime.
		void update(float deltaTime);

		// Handles an event created by the specified window.
		void handle(sf::Window &window, sf::Event &event);

		// Adds the specified widget to the screen.
		void addWidget(Widget *widget);

		// Removes the specified widget to the screen.
		void removeWidget(Widget *widget);

		// Sets the function which will be called after the screen's size changed.
		void setSizeChangedFun(std::function<void(unsigned int, unsigned int)> sizeChangedFun);

	protected:
		//virtual void onSizeChanged(unsigned int width, unsigned int height) = 0;

	private:
		std::unordered_set<Widget *> widgets;
		std::function<void(unsigned int, unsigned int)> sizeChangedFun;
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

	inline void Screen::setSizeChangedFun(std::function<void(unsigned int, unsigned int)> sizeChangedFun)
	{
		this->sizeChangedFun = sizeChangedFun;
	}
}