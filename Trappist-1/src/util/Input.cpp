#include <Trappist-1\util\Input.hpp>
#include <vector>

namespace Input 
{
	const sf::Window *window;

	std::vector<bool> keysPressedLast(sf::Keyboard::KeyCount);
	std::vector<bool> buttonsPressedLast(sf::Mouse::ButtonCount);

	void updateKey(sf::Keyboard::Key key, bool pressed)
	{
		keysPressedLast[key] = pressed;
	}

	void updateButton(sf::Mouse::Button button, bool pressed)
	{
		buttonsPressedLast[button] = pressed;
	}

	void setWindow(const sf::Window *window)
	{
		Input::window = window;
	}

	//Keyboard

	bool getKeyDown(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key) && !keysPressedLast[key];
	}

	bool getKeyPressed(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key);
	}

	bool getKeyUp(sf::Keyboard::Key key)
	{
		return !sf::Keyboard::isKeyPressed(key) && keysPressedLast[key];
	}

	//Mouse

	bool getMouseDown(sf::Mouse::Button button)
	{
		return sf::Mouse::isButtonPressed(button) && !buttonsPressedLast[button];
	}

	bool getMousePressed(sf::Mouse::Button button)
	{
		return sf::Mouse::isButtonPressed(button);
	}

	bool getMouseUp(sf::Mouse::Button button)
	{
		return !sf::Mouse::isButtonPressed(button) && buttonsPressedLast[button];
	}

	sf::Vector2i getMousePos()
	{
		return sf::Mouse::getPosition(*window);
	}
}