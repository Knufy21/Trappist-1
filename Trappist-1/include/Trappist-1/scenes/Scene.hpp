#pragma once

#include <Trappist-1\ui\Screen.hpp>

class Renderer2D;
class LightRenderer2D;
class Scene : public ui::Screen
{
	friend class Core;
public:
	enum class Type { NONE, GAME, MENU };

	Scene();
	virtual ~Scene();

	// Updates the Scene.
	virtual void update();

	// Renders the light into the scene. This function should be called before the actual render.
	virtual void renderLights(LightRenderer2D &lightRenderer2d);

	// Renders the scene.
	virtual void render(Renderer2D &renderer2d);

	// Event being called when the size of the window has been changed.
	virtual void onSizeChanged(unsigned int width, unsigned int height) override;

	// Returns what kind of scene it is.
	Scene::Type getSceneType() const;

protected:
	Scene::Type type;
};

// Inline

inline Scene::Type Scene::getSceneType() const
{
	return this->type;
}
