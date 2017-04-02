#pragma once

#include <Trappist-1\graphics\Texture.hpp>
#include <Trappist-1\scenes\Scene.hpp>

class Player;
class SceneGame : public Scene
{
public:
	SceneGame();
	~SceneGame();

	virtual void update();
	virtual void render(Renderer2D &renderer2d) override;

	virtual void onSizeChanged(unsigned int width, unsigned int height) override;

	// Returns whether the Game is Paused.
	bool isPaused() const;

private:
	// Checks for important input like menu calls etc. May influence paused.
	void inputUpdate();

	// Checks for WASD input and moves the player.
	void playerMovement();

	Player *player;
	Texture texPlayer;
	Texture testTexture;
	bool paused;
};

inline bool SceneGame::isPaused() const
{
	return paused;
}
