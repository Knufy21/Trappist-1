#pragma once

//#define D_SCL_SECURE_NO_WARNINGS
//#define _SCL_SECURE_NO_WARNINGS

#include <Trappist-1\scenes\Scene.hpp>
#include <string>
#include <SFML\Graphics.hpp>

class Core 
{
public:
	Core();
	~Core();

	// Called once at start. Contains the main-loop.
	void run();

	static void changeScene(SceneType type);

	// Writes the message into the console via std::cout and ends the line.
	static void log(const std::string &message);

	// Terminates the program after the current updatecycle.
	static void exit();

	static sf::Vector2i windowSize;
private:
	// Creates the window and returns the size of it.
	sf::Vector2i createWindow();

	static bool running;
	sf::Window *window;
	
	Scene *scene;
};
