#pragma once

enum class SceneType
{
	NULL0,
	SCENEGAME
};

#include <SFML\Graphics.hpp>


class Renderer2D;

class Scene
{
public:
	Scene(){}
	virtual ~Scene() {}

	// Updates the Scene.
	virtual void update() {}

	// Renders the Scene.
	virtual void render(Renderer2D &renderer2d) {}

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
