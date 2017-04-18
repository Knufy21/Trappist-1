#include <Trappist-1\util\Input.hpp>
#include <vector>

namespace Input 
{
	const sf::Window *window;

	std::vector<bool> keysPressedLast(sf::Keyboard::KeyCount);
	std::vector<bool> keysPressedNow(sf::Keyboard::KeyCount);
	std::vector<bool> buttonsPressedLast(sf::Mouse::ButtonCount);
	std::vector<bool> buttonsPressedNow(sf::Mouse::ButtonCount);

	void cleanUp()
	{
		keysPressedLast = keysPressedNow;
		buttonsPressedLast = buttonsPressedNow;
	}

	void updateKey(sf::Keyboard::Key key, bool pressed)
	{
		if (key != sf::Keyboard::Key::Unknown)
		{
			keysPressedNow[key] = pressed;
		}
	}

	void updateButton(sf::Mouse::Button button, bool pressed)
	{
		buttonsPressedNow[button] = pressed;
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

	glm::ivec2 getMousePos()
	{
		sf::Vector2i pos = sf::Mouse::getPosition(*window);
		return glm::ivec2(pos.x, pos.y);
	}
}