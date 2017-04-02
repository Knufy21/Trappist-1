#pragma once

#include <Trappist-1\scenes\Scene.hpp>
#include <Trappist-1\ui\widgets\Button.hpp>

class SceneMenu : public Scene
{
	using BASE = Scene;
public:
	SceneMenu();
	virtual ~SceneMenu();

	virtual void update() override;

	virtual void render(Renderer2D &renderer2d) override;

	virtual void onSizeChanged(unsigned int width, unsigned int height) override;

private:
	ui::Button btnPlay;
	ui::Button btnOptions;
	ui::Button btnExit;
	ui::Label lblTitle;
};