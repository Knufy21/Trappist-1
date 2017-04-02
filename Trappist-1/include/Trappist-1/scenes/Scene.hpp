#pragma once

enum class SceneType
{
	NONE,
	GAME,
	MENU
};

#include <SFML\Graphics.hpp>

#include <Trappist-1\ui\Screen.hpp>
#include <Trappist-1\util\Time.hpp>

class Renderer2D;

class Scene : public ui::Screen
{
	friend class Core;
public:
	Scene() {  }
	virtual ~Scene() { }

	// Updates the Scene.
	virtual void update()
	{
		Screen::update(Time::deltaTime);
	}

	// Renders the Scene.
	virtual void render(Renderer2D &renderer2d)
	{
		submit(renderer2d);
	}

	// Event being called when the size of the window has been changed.
	virtual void onSizeChanged(unsigned int width, unsigned int height) {}

	// Returns what kind of scene it is.
	SceneType getSceneType() const;

protected:
	SceneType type;
};

inline SceneType Scene::getSceneType() const
{
	return type;
}
