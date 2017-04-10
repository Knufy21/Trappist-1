#include <Trappist-1\scenes\SceneMenu.hpp>

#include <Trappist-1\Core.hpp>
#include <Trappist-1\util\Input.hpp>

#include <Trappist-1\ui\Listeners.hpp>
#include <Trappist-1\ui\Actions.hpp>
#include <Trappist-1\TextureManager.hpp>

constexpr float buttonHightlightTime = 0.06f;
constexpr float buttonPressTime = 0.06f;
constexpr float labelFadeInTime = 0.05f;
constexpr float labelFadeOutTime = 0.05f;

SceneMenu::SceneMenu()
	: focusedPlanet(SceneMenu::IMG_PLANETS_SIZE), state(SceneMenu::State::STANDARD)
{	
	type = (Scene::Type::MENU);

	for (std::size_t i = 0; i < SceneMenu::LBL_SIZE; ++i)
	{
		lbls[i].setFont(Core::font);
		lbls[i].setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
		addWidget(&lbls[i]);
	}

	lbls[SceneMenu::LBL_TITLE].setTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	lbls[SceneMenu::LBL_TITLE].setTextOutlineColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lbls[SceneMenu::LBL_TITLE].setTextThickness(0.05f);
	lbls[SceneMenu::LBL_TITLE].setTextOutlineThickness(0.2f);
	lbls[SceneMenu::LBL_TITLE].setFontSize(60);
	lbls[SceneMenu::LBL_TITLE].setTextAlignment(ui::Label::Alignment::CENTER);
	lbls[SceneMenu::LBL_TITLE].setText("Trappist-1");
	lbls[SceneMenu::LBL_TITLE].setOrigin(300.0f, 0.0f);
	lbls[SceneMenu::LBL_TITLE].setSize(600.0f, 0.0f);
	lbls[SceneMenu::LBL_TITLE].setAutoSizeMode(ui::Label::AutoSizeMode::Y);

	lbls[SceneMenu::LBL_MAIN_INFO].setTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	lbls[SceneMenu::LBL_MAIN_INFO].setTextOutlineColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lbls[SceneMenu::LBL_MAIN_INFO].setTextThickness(0.08f);
	lbls[SceneMenu::LBL_MAIN_INFO].setTextOutlineThickness(0.2f);
	lbls[SceneMenu::LBL_MAIN_INFO].setFontSize(40);
	lbls[SceneMenu::LBL_MAIN_INFO].setTextAlignment(ui::Label::Alignment::CENTER);
	lbls[SceneMenu::LBL_MAIN_INFO].setText(STR_CHOOSE_INFO);
	lbls[SceneMenu::LBL_MAIN_INFO].setAutoSizeMode(ui::Label::AutoSizeMode::Y);

	lbls[SceneMenu::LBL_PLANET_INFO].setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lbls[SceneMenu::LBL_PLANET_INFO].setTextOutlineColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	lbls[SceneMenu::LBL_PLANET_INFO].setTextThickness(0.0f);
	lbls[SceneMenu::LBL_PLANET_INFO].setTextOutlineThickness(0.0f);
	lbls[SceneMenu::LBL_PLANET_INFO].setFontSize(20u);
	lbls[SceneMenu::LBL_PLANET_INFO].setTextAlignment(ui::Label::Alignment::LEFT);
	lbls[SceneMenu::LBL_PLANET_INFO].setAutoSizeMode(ui::Label::AutoSizeMode::NONE);

	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setTextOutlineColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setTextThickness(0.0f);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setTextOutlineThickness(0.0f);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setFontSize(20u);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setTextAlignment(ui::Label::Alignment::LEFT);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setAutoSizeMode(ui::Label::AutoSizeMode::NONE);

	/* objects */
	TextureManager::load(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS, "res/textures/system");
	TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->setSmooth(false);

	imgTrappist1a.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1a"));
	imgTrappist1a.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	
	addWidget(&imgTrappist1a);

	for (std::size_t i = 0; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
	{
		imgPlanets[i].setEventReceiver(true);
		imgPlanets[i].setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord(SceneMenu::STR_PLANET_NAMES[i]));
		imgPlanets[i].setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
		imgPlanets[i].addListener(ui::CursorEnterListener([this, i](const void *args)
		{
			if (!this->isAnyPlanetFocused())
			{
				const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
				if (e->entered)
				{
					this->imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

					this->lbls[SceneMenu::LBL_PLANET_INFO].setText(SceneMenu::STR_PLANET_INFO[i]);
					this->lbls[SceneMenu::LBL_PLANET_INFO].addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
				}
				else
				{
					this->imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));

					//this->lbls[SceneMenu::LBL_PLANET_INFO].addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
					this->lbls[SceneMenu::LBL_PLANET_INFO].setText("");
				}
			}
		}));
		imgPlanets[i].addListener(ui::MouseButtonListener([this, i](const void *args)
		{
			if (!this->isAnyPlanetFocused())
			{
				const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
				if (e->pressed)
				{
					this->imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
				}
				else
				{
					this->imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));
//					this->lbls[SceneMenu::LBL_PLANET_INFO].setText("");
					this->focusPlanet(i);
				}
			}
		}));
		addWidget(&imgPlanets[i]);
	}

	/* buttons */
	
	#define buttonColorDefault glm::vec4(0.9f, 0.9f, 1.0f, 0.2f)
	#define buttonColorHighlighted glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)
	#define buttonColorPressed glm::vec4(1.0f, 1.0f, 1.0f, 0.4f)

	for (std::size_t i = 0; i < SceneMenu::BTN_SIZE; ++i)
	{
		btns[i].setEventReceiver(true);
		btns[i].setColor(buttonColorDefault);
		btns[i].setSize(SceneMenu::BTN_WIDTH, SceneMenu::BTN_HEIGHT);
		btns[i].setOrigin(SceneMenu::BTN_WIDTH * 0.5f, SceneMenu::BTN_HEIGHT * 0.5f);
		btns[i].setFont(Core::font);
		btns[i].setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		btns[i].setFontSize(30u);
		btns[i].setTextAlignment(ui::Label::Alignment::CENTER);
		//btns[i].setAutoSizeMode(ui::Label::AutoSizeMode::Y);
		btns[i].setText(SceneMenu::STR_BUTTON_NAMES[i]);
		btns[i].addListener(ui::MouseButtonListener([this, i](const void *args)
		{
			const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
			if (e->pressed)
			{
				this->btns[i].setColor(buttonColorPressed);
			}
			else
			{
				this->btns[i].setColor(buttonColorHighlighted);

				// button actions go here
				switch (i)
				{
				default:
				case SceneMenu::BTN_OPTIONS:
					showOptions();
					break;
				case SceneMenu::BTN_CREDITS:
					showCredits();
					break;
				case SceneMenu::BTN_QUIT:
					Core::exit();
					break;
				case SceneMenu::BTN_MULTIPLAYER:
					// TODO: implement
					break;
				case SceneMenu::BTN_SINGLEPLAYER:
					Core::queryScene(Scene::Type::GAME);
					break;
				}
			}
		}));
		btns[i].addListener(ui::CursorEnterListener([this, i](const void *args)
		{
			const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
			if (e->entered)
			{
				this->btns[i].setColor(buttonColorHighlighted);
				this->btns[i].addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
			}
			else
			{
				this->btns[i].setColor(buttonColorDefault);
				this->btns[i].addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			}
		}));
		addWidget(&btns[i]);
	}

	onSizeChanged(Core::windowSize.x, Core::windowSize.y);
}

SceneMenu::~SceneMenu()
{

}

void SceneMenu::update()
{
	BASE::update();

	if (getState() == SceneMenu::State::PLANET_INFO && Input::getKeyPressed(sf::Keyboard::Escape))
		unfocusPlanet();
	else if (getState() == SceneMenu::State::CREDITS && (Input::getMousePressed(sf::Mouse::Button::Left) || Input::getKeyPressed(sf::Keyboard::Escape)))
		hideCredits();
	if (getState() == SceneMenu::State::OPTIONS && Input::getKeyPressed(sf::Keyboard::Escape))
		hideOptions();
}

void SceneMenu::render(Renderer2D &renderer2d)
{
	BASE::render(renderer2d);
}

void SceneMenu::focusPlanet(std::size_t index)
{
	std::size_t lastFocusedPlanet = focusedPlanet;
	focusedPlanet = index;

	constexpr float duration = 0.6f;

	if (isAnyPlanetFocused()) // if focus planet call is valid (-> make planet focused)
	{
		setState(SceneMenu::State::PLANET_INFO);

		imgPlanets[index].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, focusedPlanetPosition, duration));
		imgPlanets[index].addAction(ui::Vec2Action(ui::Vec2Action::SCALE_TO, glm::vec2(4.0f, 4.0f), duration));

		hidePlanets(index, index + 1, duration);

		lbls[LBL_PLANET_INFO].setText("");
		lbls[LBL_PLANET_PLAY_INFO].setText(SceneMenu::STR_PLANET_INFO[index]);

		showPlayButtons(duration);
		hideStandardButtons(duration);
	}
	else // if focus planet call is invalid (-> make planet unfocused)
	{
		setState(SceneMenu::State::STANDARD);

		imgPlanets[lastFocusedPlanet].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[lastFocusedPlanet], planetYPosition), duration));
		imgPlanets[lastFocusedPlanet].addAction(ui::Vec2Action(ui::Vec2Action::SCALE_TO, glm::vec2(1.0f, 1.0f), duration));

		showPlanets(lastFocusedPlanet, lastFocusedPlanet + 1, duration);

		//lbls[LBL_PLANET_INFO].setText(SceneMenu::STR_PLANET_INFO[lastFocusedPlanet]);
		lbls[LBL_PLANET_PLAY_INFO].setText("");

		hidePlayButtons(duration);
		showStandardButtons(duration);
	}
}

void SceneMenu::showCredits()
{
	if (isAnyPlanetFocused() || getState() == SceneMenu::State::CREDITS)
		return;

	setState(SceneMenu::State::CREDITS);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_CREDITS);

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	hidePlanets(planetSplitIndex, planetSplitIndex, duration);
	hideStandardButtons(duration);
}

void SceneMenu::hideCredits()
{
	if (getState() != SceneMenu::State::CREDITS)
		return;

	setState(SceneMenu::State::STANDARD);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_CHOOSE_INFO);

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	showPlanets(planetSplitIndex, planetSplitIndex, duration);
	showStandardButtons(duration);
}

void SceneMenu::showOptions()
{
	if (isAnyPlanetFocused() || getState() == SceneMenu::State::OPTIONS)
		return;

	setState(SceneMenu::State::OPTIONS);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_BUTTON_NAMES[SceneMenu::BTN_OPTIONS]);

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	hidePlanets(planetSplitIndex, planetSplitIndex, duration);
	hideStandardButtons(duration);
}

void SceneMenu::hideOptions()
{
	if (getState() != SceneMenu::State::OPTIONS)
		return;

	setState(SceneMenu::State::STANDARD);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_CHOOSE_INFO);

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	showPlanets(planetSplitIndex, planetSplitIndex, duration);
	showStandardButtons(duration);
}

void SceneMenu::hidePlanets(std::size_t leftSplitIndex, std::size_t rightSplitIndex, float duration)
{
	// hide tr1a
	imgTrappist1a.addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(-planetXOffset, 0.0f), duration));

	// hide left planets
	for (std::size_t i = 0; i < leftSplitIndex; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i] - planetXOffset, planetYPosition), duration));

	// hide right planets
	for (std::size_t i = rightSplitIndex; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i] + planetXOffset, planetYPosition), duration));
}

void SceneMenu::showPlanets(std::size_t leftSplitIndex, std::size_t rightSplitIndex, float duration)
{
	// show tr1a
	imgTrappist1a.addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(0.0f, 0.0f), duration));

	// show left planets
	for (std::size_t i = 0; i < leftSplitIndex; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i], planetYPosition), duration));

	// show right planets
	for (std::size_t i = rightSplitIndex; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i], planetYPosition), duration));
}

void SceneMenu::hideStandardButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(baseBtnPosition.x + baseBtnXOffset, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * i), duration));
}

void SceneMenu::showStandardButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(baseBtnPosition.x, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * i), duration));
}

void SceneMenu::hidePlayButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(baseBtnPosition.x + baseBtnXOffset, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * (i - SceneMenu::BTN_PLAY_BEGIN)), duration));
}

void SceneMenu::showPlayButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(baseBtnPosition.x, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * (i - SceneMenu::BTN_PLAY_BEGIN)), duration));
}

void SceneMenu::onSizeChanged(unsigned int width, unsigned int height)
{
	float widthf = static_cast<float>(width);
	float heightf = static_cast<float>(height);

	float heighth = heightf * 0.5f;
	float widthh = widthf * 0.5f;
	float ratio = widthf / heightf;

	/* objects */

	planetXOffset = widthf;

	FloatRect rect = imgTrappist1a.getTextureRect();
	imgTrappist1a.setSize(((rect.width * imgTrappist1a.getTexture()->getSize().x) / (rect.height * imgTrappist1a.getTexture()->getSize().y)) * heightf, heightf);

	constexpr float objectHeightMultiplicator = 0.15f;

	planetYPosition = heighth;
	focusedPlanetPosition.x = widthf * 0.2f;
	focusedPlanetPosition.y = heighth;
	if (getState() == SceneMenu::State::STANDARD) // reset planet position
	{
		for (std::size_t i = 0; i < SceneMenu::IMG_PLANETS_SIZE - 1; ++i)
		{
			rect = imgPlanets[i].getTextureRect();
			imgPlanets[i].setSize(((rect.width * imgPlanets[i].getTexture()->getSize().x) / (rect.height * imgPlanets[i].getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
			imgPlanets[i].setOrigin(imgPlanets[i].getSize() * 0.5f);
			planetXPositions[i] = widthf * (static_cast<float>(i) * 0.1f + 0.28f);
			imgPlanets[i].setPosition(planetXPositions[i], planetYPosition);
		}
	}
	else // reset planet position plus offset
	{
		for (std::size_t i = 0; i < SceneMenu::IMG_PLANETS_SIZE - 1; ++i)
		{
			rect = imgPlanets[i].getTextureRect();
			imgPlanets[i].setSize(((rect.width * imgPlanets[i].getTexture()->getSize().x) / (rect.height * imgPlanets[i].getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
			imgPlanets[i].setOrigin(imgPlanets[i].getSize() * 0.5f);
			planetXPositions[i] = widthf * (static_cast<float>(i) * 0.1f + 0.28f);
		}
		if (isAnyPlanetFocused()) // split on focused
		{
			hidePlanets(focusedPlanet, focusedPlanet + 1, 0.0f); // TODO: find better fix than duration 0.0f
			imgPlanets[focusedPlanet].setPosition(focusedPlanetPosition); // move focussed planet to correct position
		}
		else // split default
		{
			hidePlanets(3, 3, 0.0f); // TODO: find better fix than duration 0.0f
		}
	}
	// TODO: fix standard button comeback when options or credits state and window is resized
	baseBtnPosition.x = widthf * 0.8f;
	baseBtnPosition.y = heightf * 0.9f;
	baseBtnXOffset = widthf * 0.2f + 400.0f;
	if (isAnyPlanetFocused()) // play buttons shown
	{
		for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
			btns[i].setPosition(baseBtnPosition.x + baseBtnXOffset, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * i);
		for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
			btns[i].setPosition(baseBtnPosition.x, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * (i - SceneMenu::BTN_PLAY_BEGIN));
	}
	else // standard buttons shown
	{
		for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
			btns[i].setPosition(baseBtnPosition.x, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * i);
		for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
			btns[i].setPosition(baseBtnPosition.x + baseBtnXOffset, baseBtnPosition.y - (SceneMenu::BTN_HEIGHT + 10.0f) * (i - SceneMenu::BTN_PLAY_BEGIN));
	}

	lbls[SceneMenu::LBL_TITLE].setPosition(widthh, heightf * 0.01f);

	lbls[SceneMenu::LBL_MAIN_INFO].setPosition(widthh, lbls[SceneMenu::LBL_TITLE].getPosition().y + heightf * 0.15f);
	lbls[SceneMenu::LBL_MAIN_INFO].setOrigin(widthh * 0.94f, 0.0f);
	lbls[SceneMenu::LBL_MAIN_INFO].setSize(widthf * 0.94f, 0.0f);

	lbls[SceneMenu::LBL_PLANET_INFO].setPosition(widthh, heightf * 0.6f);
	lbls[SceneMenu::LBL_PLANET_INFO].setOrigin(widthh * 0.6f, 0.0f);
	lbls[SceneMenu::LBL_PLANET_INFO].setSize(widthf * 0.6f, 0.0f);

	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setPosition(widthf * 0.8f, heightf * 0.3f);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setSize(widthf * 0.6f, 0.0f);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setOrigin(widthh * 0.3f, 0.0f);
}