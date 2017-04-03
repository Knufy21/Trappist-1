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
	ui::Button btnOptions;
	ui::Button btnCredits;
	ui::Button btnQuit;

	ui::Label lblTitle;

	ui::Label lblChooseInfo;

	ui::Image imgTrappist1a;
	ui::Image imgTrappist1b;
	ui::Image imgTrappist1c;
	ui::Image imgTrappist1d;
	ui::Image imgTrappist1e;
	ui::Image imgTrappist1f;
	ui::Image imgTrappist1g;
	ui::Image imgTrappist1h;

	//ui::Label lblTrappist1aInfo;
	ui::Label lblPlanetInfo;
};