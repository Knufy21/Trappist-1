#pragma once

#include <Trappist-1\scenes\Scene.hpp>
#include <Trappist-1\ui\widgets\Button.hpp>

class SceneMenu : public Scene
{
	using BASE = Scene;
public:
	// Images
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_B	=	0;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_C	=	1;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_D	=	2;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_E	=	3;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_F	=	4;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_G	=	5;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_H	=	6;
	static constexpr std::size_t IMG_PLANETS_TRAPPIST_1_R	=	7;
	static constexpr std::size_t IMG_PLANETS_SIZE			=	8;
	// Buttons
	static constexpr std::size_t BTN_QUIT					=	0;
	static constexpr std::size_t BTN_CREDITS				=	1;
	static constexpr std::size_t BTN_OPTIONS				=	2;
	static constexpr std::size_t BTN_MULTIPLAYER			=	3;
	static constexpr std::size_t BTN_SINGLEPLAYER			=	4;
	static constexpr std::size_t BTN_SIZE					=	5;
	static constexpr std::size_t BTN_PLAY_BEGIN				=	SceneMenu::BTN_MULTIPLAYER;
	static constexpr std::size_t BTN_PLAY_END				=	SceneMenu::BTN_SINGLEPLAYER + 1;
	static constexpr std::size_t BTN_STD_BEGIN				=	SceneMenu::BTN_QUIT;
	static constexpr std::size_t BTN_STD_END				=	SceneMenu::BTN_OPTIONS + 1;
	static constexpr float BTN_WIDTH						=	250.0f;
	static constexpr float BTN_HEIGHT						=	50.0f;
	// Labels
	static constexpr std::size_t LBL_TITLE					=	0;
	static constexpr std::size_t LBL_MAIN_INFO				=	1;
	static constexpr std::size_t LBL_PLANET_INFO			=	2;
	static constexpr std::size_t LBL_PLANET_PLAY_INFO		=	3;
	static constexpr std::size_t LBL_SIZE					=	4;
	static constexpr const char *STR_PLANET_NAMES[SceneMenu::IMG_PLANETS_SIZE + 1] =
	{
		"Trappist-1b",
		"Trappist-1c",
		"Trappist-1d",
		"Trappist-1e",
		"Trappist-1f",
		"Trappist-1g",
		"Trappist-1h",
		"Trappist-1r",
		"Trappist-1q"
	};

	static constexpr const char *STR_PLANET_INFO[SceneMenu::IMG_PLANETS_SIZE + 1] =
	{
		"Trappist-1 b\nOrbital period: 1.51 days\nDistance to star: 0.011 AU\nRadius: 1.09 earth radii\nMass: 0.85 earths",
		"Trappist-1 c\nOrbital period: 2.42 days\nDistance to star: 0.015 AU\nRadius: 1.06 earth radii\nMass: 1.38 earths",
		"Trappist-1 d\nOrbital period: 4.05 days\nDistance to star: 0.021 AU\nRadius: 0.77 earth radii\nMass: 0.41 earths",
		"Trappist-1 e\nOrbital period: 6.10 days\nDistance to star: 0.028 AU\nRadius: 0.92 earth radii\nMass: 0.62 earths",
		"Trappist-1 f\nOrbital period: 9.21 days\nDistance to star: 0.037 AU\nRadius: 1.04 earth radii\nMass: 0.68 earths",
		"Trappist-1 g\nOrbital period: 12.35 days\nDistance to star: 0.045 AU\nRadius: 1.13 earth radii\nMass: 1.34 earths",
		"Trappist-1 h\nOrbital period: ~20 days\nDistance to star: ~0.06 AU\nRadius: 0.76 earth radii\nMass: ?",
		"Random planet\nOrbital period: ? days\nDistance to star: ? AU\nRadius: ? earth radii\nMass: ?",
		"Locked planet\nOrbital period: ? days\nDistance to star: ? AU\nRadius: ? earth radii\nMass: ?"

	};

	static constexpr const char *STR_BUTTON_NAMES[SceneMenu::BTN_SIZE] =
	{
		"Quit",
		"Credits",
		"Options",
		"Multiplayer",
		"Singleplayer"
	};

	static constexpr const char *STR_CREDITS = "Programming\n\nBromBear\nKnufy21\n\nDesign\n\nBromBear\nKnufy21";
	static constexpr const char *STR_CHOOSE_INFO = "Choose a planet to play on";
	
	enum class State { STANDARD, PLANET_INFO, CREDITS, OPTIONS };

	SceneMenu();
	virtual ~SceneMenu();

	virtual void update() override;

	virtual void render(Renderer2D &renderer2d) override;

	// Focusses the planet with the specified index.
	void focusPlanet(std::size_t index);

	// Unfocuses the currently focused planet.
	void unfocusPlanet();

	// Shows the credits of the game. If the credits are already shown or if any planet is focused, this function call has no effect.
	void showCredits();

	// Hides the credits of the game. If the credits are not shown, this function call has no effect.
	void hideCredits();

	// Shows the options of the game. If the credits are already shown or if any planet is focused, this function call has no effect.
	void showOptions();

	// Hides the options of the game. If the credits are not shown, this function call has no effect.
	void hideOptions();

	bool isAnyPlanetFocused() const;

	// Sets the state of the menu scene.
	void setState(SceneMenu::State state);

	// Returns the state of the menu scene.
	SceneMenu::State getState() const;

	// Returns whether the speicified state is currently active or not.
	bool isState(SceneMenu::State state) const;

	// Hides all planets and trappist-1a in the specified duration.
	//All planets with an index less or equal to leftSplitIndex move to the left and all planets with an index greater to rightSplitIndex move to the right.
	void hidePlanets(std::size_t leftSplitIndex, std::size_t rightSplitIndex, float duration);

	// Shows all planets and trappist-1a in the specified duration.
	//All planets with an index less or equal to leftSplitIndex come from the left and all planets with an index greater to rightSplitIndex come from the right.
	void showPlanets(std::size_t leftSplitIndex, std::size_t rightSplitIndex, float duration);

	// Hides all standard buttons in the specified duration.
	void hideStandardButtons(float duration);

	// Shows all standard buttons in the specified duration.
	void showStandardButtons(float duration);

	// Hides all play buttons in the specified duration.
	void hidePlayButtons(float duration);

	// Shows all play buttons in the specified duration.
	void showPlayButtons(float duration);

	// Sets the color of the img player using the specified position.
	void setImgPlayerColorByPosition(const glm::vec2 &position);

	virtual void onSizeChanged(unsigned int width, unsigned int height) override;

private:
	// Returns the width of the screen (inline).
	float width() const;

	// Returns the height of the screen (inline).
	float height() const;

	// Returns half the width of the screen (inline).
	float half_width() const;

	// Returns half the height of the screen (inline).
	float half_height() const;

	/* Button inline methods */

	// Returns the base x position of the shown buttons (inline).
	float button_shown_x() const;

	// Returns the base x position of the hidden buttons (inline).
	float button_hidden_x() const;

	// Returns the base y position of the buttons (inline).
	float button_base_y() const;

	// Returns the y offset between the buttons (inline).
	float button_offset_y() const;

	/* Planet inline */

	// Returns the y position of the planets and trappist-1a (inline).
	float planet_y() const;

	// Returns the positive x offset of the planet when hidden (inline).
	float planet_offset_x() const;

	// Returns the x position of the focused planet (inline).
	float planet_focused_x() const;

	// Returns the y position of the focused planet (inline).
	float planet_focused_y() const;

	/* Player inline */

	// Returns the x position of the player for when any planet is focused.
	float player_focused_x() const;

	// Returns the y position of the player for when any planet is focused.
	float player_focused_y() const;

	SceneMenu::State state;
	ui::Image imgTrappist1a;
	ui::Image imgPlanets[SceneMenu::IMG_PLANETS_SIZE];
	ui::Button btns[SceneMenu::BTN_SIZE];
	ui::Label lbls[SceneMenu::LBL_SIZE];
	EightBoolArray planetBoolsLocked;
	float planetXPositions[SceneMenu::IMG_PLANETS_SIZE];
	
	std::size_t focusedPlanet; // index of the currently focussed planet (PLANET_SIZE if none focussed)
	
	// player
	Texture texPlayer;
	ui::Image imgPlayer;
	glm::vec2 playerVelocity;
	float playerRoatationVelocity;

	float widthf;
	float heightf;
};

// Inline

inline void SceneMenu::unfocusPlanet()
{
	focusPlanet(SceneMenu::IMG_PLANETS_SIZE);
}

inline bool SceneMenu::isAnyPlanetFocused() const
{
	return focusedPlanet < SceneMenu::IMG_PLANETS_SIZE;
}

inline SceneMenu::State SceneMenu::getState() const
{
	return this->state;
}

inline void SceneMenu::setState(SceneMenu::State state)
{
	this->state = state;
}

inline bool SceneMenu::isState(SceneMenu::State state) const
{
	return getState() == state;
}

// True inline functions

inline float SceneMenu::width() const
{
	return this->widthf;
}

inline float SceneMenu::height() const
{
	return this->heightf;
}

inline float SceneMenu::half_width() const
{
	return this->width() * 0.5f;
}

inline float SceneMenu::half_height() const
{
	return this->height() * 0.5f;
}

/* Button inline methods */

inline float SceneMenu::button_shown_x() const
{
	return this->width() * 0.8f;
}

inline float SceneMenu::button_hidden_x() const
{
	return this->width() + 400.0f;
}

inline float SceneMenu::button_base_y() const
{
	return this->height() * 0.9f;
}

inline float SceneMenu::button_offset_y() const
{
	return SceneMenu::BTN_HEIGHT + 10.0f;
}

/* Planet inline */

inline float SceneMenu::planet_y() const
{
	return half_height();
}

inline float SceneMenu::planet_offset_x() const
{
	return width();
}

inline float SceneMenu::planet_focused_x() const
{
	return width() * 0.2f;
}

inline float SceneMenu::planet_focused_y() const
{
	return half_height();
}

/* Player inline */

inline float SceneMenu::player_focused_x() const
{
	return planet_focused_x();
}

inline float SceneMenu::player_focused_y() const
{
	return planet_focused_y() * 0.3f;
}