#include <Trappist-1\Core.hpp>
#include <Trappist-1\Util.hpp>

#include <Trappist-1\graphics\Renderer2D.hpp>
#include <Trappist-1\graphics\Shader.hpp>

#include <Trappist-1\scenes\SceneGame.hpp>
#include <iostream>
#include <GL\glew.h>

#include <Trappist-1\util\TexturePacker.hpp>
#include <Trappist-1\TextureAtlas.hpp>

//#define TESTING
#ifdef TESTING

void printElapsed(const Timer &timer)
{
	std::cout << "Elapsed time: " << timer.elapsedMilliseconds() << "ms";
}

void printElapsedStats(const Timer &timer, size_t count, size_t amount)
{
	double elapsed = timer.elapsedNanoseconds();
	std::cout << "Elapsed time: " << elapsed << "ns (total), " << elapsed / static_cast<double>(count * amount) << "ns (average)\n\n";
}

#define TYPE char

void prepareTest(Timer &timer, TYPE *src, size_t amount)
{
	for (size_t i = 0; i < amount; ++i)
		src[i] = i;
	timer.reset();
}

int main()
{
	Timer t;

	constexpr size_t count = 5;
	constexpr size_t amount = 1'000'000'000;
	constexpr size_t bytes = amount * sizeof(TYPE);

	for (size_t x = 0; x < count; ++x)
	{
		std::cout << "Allocating " << static_cast<long double>(bytes) / 1'000'000.0 << " mega bytes of memory...";
		TYPE *src = new TYPE[amount];
		std::cout << " done\n";

		std::cout << "Deallocating " << static_cast<long double>(bytes) / 1'000'000.0 << " mega bytes of memory...";
		delete[] src;
		std::cout << " done\n";
	}

	return 0;

	std::cout << "Allocating " << static_cast<long double>(bytes) / 1'000'000.0 << " mega bytes of memory...";
	TYPE *src = new TYPE[amount];
	std::cout << " done\n";
	std::cout << "Allocating " << static_cast<long double>(bytes) / 1'000'000.0 << " mega bytes of memory...";
	TYPE *dst = new TYPE[amount];
	std::cout << " done\n";
	//TYPE src[count];
	//TYPE dst[count];

	std::cout << "for loop (pre inc):\n";
	prepareTest(t, src, amount);
	for (size_t x = 0; x < count; ++x)
	{
		for (size_t i = 0; i < amount; ++i)
			dst[i] = src[i];
	}
	printElapsedStats(t, count, amount);

	std::cout << "for loop (post inc):\n";
	prepareTest(t, src, amount);
	for (size_t x = 0; x < count; ++x)
	{
		for (size_t i = 0; i < amount; i++)
			dst[i] = src[i];
	}
	printElapsedStats(t, count, amount);

	std::cout << "memcopy:\n";
	prepareTest(t, src, amount);
	for (size_t x = 0; x < count; ++x)
	{
		memcpy(dst, src, bytes);
	}
	printElapsedStats(t, count, amount);

	std::cout << "std::copy:\n";
	prepareTest(t, src, amount);
	for (size_t x = 0; x < count; ++x)
	{
		std::copy(dst, dst + amount, src);
	}
	printElapsedStats(t, count, amount);

	std::cout << "end\n";

	delete[] dst;
	delete[] src;

	return 0;
}

#else

int main()
{
	Core core;
	core.run();

	return 0;
}

#endif // TESTING

bool Core::running = false;
sf::Vector2i Core::windowSize;

Core::Core()
{
	windowSize = createWindow();
	//scene = new Scene();
	TexturePacker::packFolder("res/textures/tiles", "res/textures", "tiles", 128, 128);
	scene = new SceneGame();
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
		if (err != GLEW_OK)
		{
			std::cout << "Error: " << glewGetErrorString(err) << "\n";
			__debugbreak();
		}
		else
			std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << "\n";
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	running = true;
	sf::Event event;

	Timer deltaTimer;
	Timer secondTimer;
	unsigned int countedFPS = 0;

	Shader shader2d("res/shaders/sprite.vert", "res/shaders/sprite.frag");

	std::string s("textures[");
	for (int i = 0; i < 32; ++i)
		shader2d.setUniform1i((s + std::to_string(i) + "]").c_str(), 0);

	//shader2d.setUniform1i("textures[0]", 0);
	//shader2d.setUniform1i("textures[1]", 1);

	Renderer2D renderer2d;
	renderer2d.setShader(&shader2d);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

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
		}

		scene->update();
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderer2d.begin();
		scene->render(renderer2d);
		renderer2d.end();
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

sf::Vector2i Core::createWindow() 
{
	//sf::VideoMode bestMode = sf::VideoMode::getFullscreenModes().front();
	//sf::Vector2i size(bestMode.width, bestMode.height);
	//window = new sf::Window(bestMode, "Trappist-1", sf::Style::Fullscreen);

	sf::Vector2i size(800, 480);
	window = new sf::Window(sf::VideoMode(size.x, size.y), "Trappist-1");
	//window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(true);
	window->setActive();

	return size;
}

//Static Methods:

void Core::log(const std::string &message)
{
	std::cout << message << std::endl;
}

void Core::exit()
{
	running = false;
}