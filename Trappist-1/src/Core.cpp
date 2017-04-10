#include <Trappist-1\Core.hpp>
#include <Trappist-1\Util.hpp>

#include <SFML\Window\Window.hpp>
#include <SFML\Window\Event.hpp>

#include <Trappist-1\graphics\Shader.hpp>
#include <Trappist-1\graphics\Renderer2D.hpp>
#include <Trappist-1\graphics\light\LightRenderer2D.hpp>

#include <Trappist-1\Scenes.hpp>
#include <iostream>
#include <GL\glew.h>

#include <Trappist-1\util\TexturePacker.hpp>
#include <Trappist-1\TextureAtlas.hpp>

#include <Trappist-1\World.hpp>

#include <Trappist-1\util\DebugLog.hpp>

int main()
{
	Core core;
	core.run();

	return 0;
}

bool Core::running = false;
glm::ivec2 Core::windowSize;
Scene *Core::scene = nullptr;
Font Core::font;
Scene::Type Core::queriedScene = Scene::Type::NONE;

Core::Core()
{
	createWindow();

	TexturePacker::packDirectory("res/textures/tiles", "res/textures/tiles", 128, 128);
	TexturePacker::packDirectory("res/textures/system", "res/textures/system", 300, 700);
	TexturePacker::packDirectory("res/textures/entities/shadow-slime", "res/textures/entities/shadow-slime", 128, 128);
	TexturePacker::packDirectory("res/textures/entities/player", "res/textures/entities/player-test", 128, 128);
	font.load("res/fonts/PixelArial.png", "res/fonts/PixelArial.fnt");
	//font.load("res/fonts/Arial/Arial.png", "res/fonts/Arial/Arial.fnt");
	changeScene(Scene::Type::GAME);
}

Core::~Core() 
{
	window->setActive(false);
	delete window;
	delete scene;
}

void Core::run()
{
	{
		GLenum err = glewInit();
		IF_ELSE(err != GLEW_OK,
			ERR("Error: " << glewGetErrorString(err)),
			LOG("Status: Using GLEW " << glewGetString(GLEW_VERSION)));
	}

	running = true;
	sf::Event event;

	Timer deltaTimer;
	Timer secondTimer;
	unsigned int countedFPS = 0;

	Shader shader2d("res/shaders/sprite.vert", "res/shaders/sprite.frag");
	Shader fontShader("res/shaders/font.vert", "res/shaders/font.frag");
	Shader lightShader("res/shaders/light.vert", "res/shaders/light.frag");

	shader2d.enable();
	shader2d.setUniform1i("lightMap", 10);

	Renderer2D renderer2d;
	renderer2d.setClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	renderer2d.setShader(&shader2d);
	renderer2d.setFontShader(&fontShader);

	LightRenderer2D lightRenderer2d;
	lightRenderer2d.setShader(&lightShader);

	Timer testTimer;

	while (running)
	{
		Time::deltaTime = deltaTimer.elapsedSeconds();
		deltaTimer.reset();
		
		while (window->pollEvent(event))
		{
			switch (event.type)
			{
			default:
				break;
			case sf::Event::Closed:
				window->close();
				exit();
				return;
			case sf::Event::Resized:
				windowSize.x = event.size.width;
				windowSize.y = event.size.height;
				glViewport(0, 0, event.size.width, event.size.height);
				if (scene)
					scene->onSizeChanged(event.size.width, event.size.height);
				break;
			case sf::Event::KeyPressed:
				Input::updateKey(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				Input::updateKey(event.key.code, false);
				break;
			case sf::Event::MouseButtonPressed:
				Input::updateButton(event.mouseButton.button, true);
				break;
			case sf::Event::MouseButtonReleased:
				Input::updateButton(event.mouseButton.button, false);
				break;
			}
			if (scene)
				scene->handle(*window, event);
		}

		if (scene && scene->type != queriedScene)
			changeScene(queriedScene);

		scene->update();

		// Render lights
		lightRenderer2d.begin();
		scene->renderLights(lightRenderer2d);
		lightRenderer2d.end();
		lightRenderer2d.flush();

		// Render sprites + fonts
		renderer2d.begin();
		testTimer.reset();
		scene->render(renderer2d);
		//std::cout << "Rendering took: " << testTimer.elapsedSeconds() << std::endl;
		renderer2d.end();
		glActiveTexture(GL_TEXTURE0 + 10);
		glBindTexture(GL_TEXTURE_2D, lightRenderer2d.getColorTextureAttachment());
		renderer2d.flush();

		window->display();

		++countedFPS;
		if (secondTimer.elapsedSeconds() >= 1.0f)
		{
			secondTimer.reset();
			std::cout << "FPS: " << countedFPS << ", deltaTime: " << Time::deltaTime << "\n";
			countedFPS = 0;
		}
	}
}

void Core::createWindow()
{
	//sf::VideoMode bestMode = sf::VideoMode::getFullscreenModes().front();
	//windowSize.x = bestMode.width;
	//windowSize.y = bestMode.height;
	//window = new sf::Window(bestMode, "Trappist-1", sf::Style::Fullscreen);

	windowSize.x = 800;
	windowSize.y = 480;
	window = new sf::Window(sf::VideoMode(windowSize.x, windowSize.y), "Trappist-1", 7u, sf::ContextSettings(8));
	//window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	window->setActive();
}

//Static Methods:

void Core::changeScene(Scene::Type type)
{
	queriedScene = type;
	delete scene;

	switch (type)
	{
	default:
	case Scene::Type::MENU:
		scene = new SceneMenu;
		break;
	case Scene::Type::GAME:
		scene = new SceneGame;
		break;
	}
}

void Core::queryScene(Scene::Type type)
{
	queriedScene = type;
}

void Core::log(const std::string &message)
{
	std::cout << message << std::endl;
}

void Core::exit()
{
	running = false;
}