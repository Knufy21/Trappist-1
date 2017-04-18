#pragma once

#include <Trappist-1\scenes\Scene.hpp>
#include <Trappist-1\graphics\Texture.hpp>

class Player;
class Entity;
class SceneGame : public Scene
{
public:
	SceneGame();
	virtual ~SceneGame();

	virtual void update() override;

	virtual void renderLights(LightRenderer2D &lightRenderer2d) override final;
	virtual void render(Renderer2D &renderer2d) override final;

	virtual void onSizeChanged(unsigned int width, unsigned int height) override;

	// Returns whether the Game is Paused.
	bool isPaused() const;

private:
	// Checks for important input like menu calls etc. May influence paused.
	void inputUpdate();

	// Checks for WASD and ability input, moves the player and casts abilities.
	void playerInput();

	Player *player;
	Texture texPlayer;
	Texture testTexture;
	bool paused;
	Entity *e4;

	// test for lights
	glm::vec2 lightEdges;
	float lightFactor;
	bool lightUp;
};

inline bool SceneGame::isPaused() const
{
	return paused;
}
