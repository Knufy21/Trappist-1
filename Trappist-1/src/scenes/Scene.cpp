#include <Trappist-1\scenes\Scene.hpp>

#include <Trappist-1\util\Time.hpp>

Scene::Scene()
{	}

Scene::~Scene()
{	}

void Scene::update()
{
	Screen::update(Time::deltaTime);
}

void Scene::renderLights(LightRenderer2D &lightRenderer2d)
{

}

void Scene::render(Renderer2D &renderer2d)
{

}

void Scene::onSizeChanged(unsigned int width, unsigned int height)
{

}