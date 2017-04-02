#include <iostream>

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <SFML\Graphics.hpp>

int main()
{
	std::cout << "Trappist-1" << std::endl;

	sf::RenderWindow window(sf::VideoMode(800, 480), "Trappist-1");
	sf::Event event;

	{
		GLenum err = glewInit();
		if (err != GLEW_OK)
		{
			std::cout << "Error: " << glewGetErrorString(err) << "\n";
			__debugbreak();
		}
		else
			std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
	}

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}

		window.display();

		window.display();
	}

	return 0;
}