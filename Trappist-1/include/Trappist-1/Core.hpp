#pragma once

//#define D_SCL_SECURE_NO_WARNINGS
//#define _SCL_SECURE_NO_WARNINGS

#include <string>
#include <glm\glm.hpp>
#include <Trappist-1\scenes\Scene.hpp>
#include <Trappist-1\graphics\fonts\Font.hpp>

namespace sf { class Window; }
class Core
{
public:
	Core();
	~Core();

	// Called once at start. Contains the main-loop.
	void run();

	// Changes the scene immediately which can cause errors with the deleted scene.
	static void changeScene(Scene::Type type);

	// Queries to change the scene before the next scene update.
	static void queryScene(Scene::Type type);

	// Writes the message into the console via std::cout and ends the line.
	static void log(const std::string &message);

	// Terminates the program after the current updatecycle.
	static void exit();

	static glm::ivec2 windowSize;
	static Font font;
private:
	// Creates the window and sets the member windowSize to the window size.
	void createWindow();

	static bool running;
	sf::Window *window;
	
	static Scene *scene;
	static Scene::Type queriedScene;
	
};
