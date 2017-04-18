#pragma once

#include <glm\glm.hpp>
#include <SFML\Window\Window.hpp>
#include <SFML\Window\Mouse.hpp>
#include <SFML\Window\Keyboard.hpp>

namespace Input
{
	void setWindow(const sf::Window *window);

	// Copies the buttons pressed now to the bottons pressed last and resets the buttons pressed now. Duh'
	void cleanUp();

	// Updates the value in keysPressedLast.
	void updateKey(sf::Keyboard::Key key, bool pressed);

	// Updates the value in buttonsPressedLast.
	void updateButton(sf::Mouse::Button button, bool pressed);

	// Returns true if the key wasnt pressed in the last update but is now
	bool getKeyDown(sf::Keyboard::Key key);

	// Returns true if the key is pressed
	bool getKeyPressed(sf::Keyboard::Key key);

	// Returns true if the key was pressed in the last update but isnt now
	bool getKeyUp(sf::Keyboard::Key key);

	//Returns true if the button wasnt pressed in the last update but is now
	bool getMouseDown(sf::Mouse::Button button);

	// Returns true if the button is pressed
	bool getMousePressed(sf::Mouse::Button button);

	// Returns true if the button was pressed in the last update but isnt now
	bool getMouseUp(sf::Mouse::Button button);

	// Return the position of the mouse in the window
	glm::ivec2 getMousePos();
}
