#include <Trappist-1\scenes\SceneMenu.hpp>

#include <Trappist-1\Core.hpp>
#include <Trappist-1\util\Input.hpp>

#include <Trappist-1\ui\Listeners.hpp>
#include <Trappist-1\ui\Actions.hpp>
#include <Trappist-1\TextureManager.hpp>
#include <Trappist-1\util\Time.hpp>
#include <Trappist-1\util\Randomf.hpp>

constexpr float buttonHightlightTime = 0.06f;
constexpr float buttonPressTime = 0.06f;
constexpr float labelFadeInTime = 0.05f;
constexpr float labelFadeOutTime = 0.05f;

SceneMenu::SceneMenu()
	: focusedPlanet(SceneMenu::IMG_PLANETS_SIZE), state(SceneMenu::State::STANDARD), planetBoolsLocked(0b0000'0000) // last, ..., second, first
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
		if(planetBoolsLocked.get(static_cast<EightBoolArray::value_t>(i)))
			imgPlanets[i].setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord(SceneMenu::STR_PLANET_NAMES[SceneMenu::IMG_PLANETS_SIZE]));
		else
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

					if (planetBoolsLocked.get(static_cast<EightBoolArray::value_t>(i)))
						this->lbls[SceneMenu::LBL_PLANET_INFO].setText(SceneMenu::STR_PLANET_INFO[SceneMenu::IMG_PLANETS_SIZE]);
					else
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

	texPlayer.load("res/textures/entities/Player.png");
	texPlayer.setSmooth(false);
	imgPlayer.setTexture(&texPlayer);
	imgPlayer.setDepthValue(-0.3f);
	addWidget(&imgPlayer);
	playerVelocity.x = 2.2f;
	playerVelocity.y = 2.6f;
	playerRoatationVelocity = 0.2f;

	/* buttons */

	TextureManager::load(TextureManager::TextureHandles::UI_ATLAS, "res/textures/ui");
	TextureManager::get(TextureManager::TextureHandles::UI_ATLAS)->setSmooth(false);
	
	#define buttonColorDefault glm::vec4(0.18f, 0.18f, 0.18f, 1.0f)
	#define buttonColorHighlighted glm::vec4(0.3f, 0.3f, 0.3f, 1.0f)
	#define buttonColorPressed glm::vec4(0.4f, 0.4f, 0.4f, 1.0f)

	for (std::size_t i = 0; i < SceneMenu::BTN_SIZE; ++i)
	{
		btns[i].setEventReceiver(true);
		btns[i].setSize(SceneMenu::BTN_WIDTH, SceneMenu::BTN_HEIGHT);
		btns[i].setOrigin(SceneMenu::BTN_WIDTH * 0.5f, SceneMenu::BTN_HEIGHT * 0.5f);
		btns[i].setFont(Core::font);
		btns[i].setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		btns[i].setFontSize(30u);
		btns[i].setTextAlignment(ui::Label::Alignment::CENTER);
		btns[i].setDepthValue(-0.9f);
		btns[i].setColor(buttonColorDefault);
		//btns[i].setTexture(TextureManager::get(TextureManager::TextureHandles::UI_ATLAS)->getTexture());
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

	if (getState() != SceneMenu::State::PLANET_INFO)
	{
		// update player velocity
		if (Input::getMousePressed(sf::Mouse::Button::Right))
		{
			playerVelocity += glm::normalize(glm::vec2(Input::getMousePos()) - imgPlayer.getPosition()) * 20.0f;
		}
		if(glm::length(playerVelocity) > 10.0f)
			playerVelocity -= glm::normalize(playerVelocity);

		// distance to sun
		setImgPlayerColorByPosition(imgPlayer.getPosition());

		// player
		imgPlayer.translate(playerVelocity.x * Time::deltaTime, playerVelocity.y * Time::deltaTime);
		imgPlayer.rotate(playerRoatationVelocity * Time::deltaTime);
		//imgPlayer.setRotation(0.0f);

		// bounce player
		if ((imgPlayer.getPosition().x < 0.0f && playerVelocity.x < 0.0f) || (imgPlayer.getPosition().x > this->width() && playerVelocity.x > 0.0f))
			playerVelocity.x *= -1;

		if ((imgPlayer.getPosition().y < 0.0f && playerVelocity.y < 0.0f) || (imgPlayer.getPosition().y > this->height() && playerVelocity.y > 0.0f))
			playerVelocity.y *= -1;
	}
}

void SceneMenu::setImgPlayerColorByPosition(const glm::vec2 &position)
{
	float distance = glm::distance(position, glm::vec2(0.0f, this->height() * 0.5f));
	float col = (distance) / (this->width() * 0.5f);
	imgPlayer.setColor(glm::vec4((2.0f - col), 0.8f, col * 0.6f, 1.0f));
}

void SceneMenu::render(Renderer2D &renderer2d)
{
	BASE::render(renderer2d);

	// Submit trappist-1a and planets
	imgTrappist1a.submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_B].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_C].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_D].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_E].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_F].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_G].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_H].submit(renderer2d);
	imgPlanets[SceneMenu::IMG_PLANETS_TRAPPIST_1_R].submit(renderer2d);

	// Submit player
	imgPlayer.submit(renderer2d);

	// Submit buttons
	btns[SceneMenu::BTN_QUIT].submit(renderer2d);
	btns[SceneMenu::BTN_CREDITS].submit(renderer2d);
	btns[SceneMenu::BTN_OPTIONS].submit(renderer2d);
	btns[SceneMenu::BTN_MULTIPLAYER].submit(renderer2d);
	btns[SceneMenu::BTN_SINGLEPLAYER].submit(renderer2d);

	// Submit labels
	lbls[SceneMenu::LBL_TITLE].submit(renderer2d);
	lbls[SceneMenu::LBL_MAIN_INFO].submit(renderer2d);
	lbls[SceneMenu::LBL_PLANET_INFO].submit(renderer2d);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].submit(renderer2d);
}

void SceneMenu::focusPlanet(std::size_t index)
{
	std::size_t lastFocusedPlanet = focusedPlanet;
	focusedPlanet = index;

	playerRoatationVelocity = Randomf::randomFloat(-1.0f, 1.0f); // Randomf used

	constexpr float duration = 0.6f;

	if (isAnyPlanetFocused()) // if focus planet call is valid (-> make planet focused)
	{
		scheduleEvent(duration, [this]()
		{
		});
		this->setState(SceneMenu::State::PLANET_INFO);

		imgPlanets[index].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planet_focused_x(), planet_focused_y()), duration));
		imgPlanets[index].addAction(ui::Vec2Action(ui::Vec2Action::SCALE_TO, glm::vec2(4.0f, 4.0f), duration));

		hidePlanets(index, index + 1, duration);

		lbls[LBL_PLANET_INFO].setText("");
		if (planetBoolsLocked.get(static_cast<EightBoolArray::value_t>(index)))
			lbls[LBL_PLANET_PLAY_INFO].setText(SceneMenu::STR_PLANET_INFO[SceneMenu::IMG_PLANETS_SIZE]);
		else
			lbls[LBL_PLANET_PLAY_INFO].setText(SceneMenu::STR_PLANET_INFO[index]);

		if(!planetBoolsLocked.get(static_cast<EightBoolArray::value_t>(index)))
			showPlayButtons(duration);
		hideStandardButtons(duration);

		// move player
		imgPlayer.addAction(ui::FloatAction(ui::FloatAction::ROTATE_TO, 0.0f, duration));
		imgPlayer.addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(player_focused_x(), player_focused_y()), duration));

		setImgPlayerColorByPosition(glm::vec2(planetXPositions[index], planet_y()));
	}
	else // if focus planet call is invalid (-> make planet unfocused)
	{
		scheduleEvent(duration, [this]()
		{
		});
		this->setState(SceneMenu::State::STANDARD);

		imgPlanets[lastFocusedPlanet].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[lastFocusedPlanet], planet_y()), duration));
		imgPlanets[lastFocusedPlanet].addAction(ui::Vec2Action(ui::Vec2Action::SCALE_TO, glm::vec2(1.0f, 1.0f), duration));

		showPlanets(lastFocusedPlanet, lastFocusedPlanet + 1, duration);

		lbls[LBL_PLANET_PLAY_INFO].setText("");

		hidePlayButtons(duration);
		showStandardButtons(duration);

		// move player
		imgPlayer.addAction(ui::FloatAction(ui::FloatAction::ROTATE_BY, playerRoatationVelocity, duration));
		imgPlayer.addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[lastFocusedPlanet], planet_y() * 0.7f), duration));

		// clamp player velocity
		playerVelocity = glm::normalize(playerVelocity) * 20.0f;
	}
}

void SceneMenu::showCredits()
{
	if (isAnyPlanetFocused() || getState() == SceneMenu::State::CREDITS)
		return;

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	scheduleEvent(duration, [this]()
	{
	});
	this->setState(SceneMenu::State::CREDITS);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_CREDITS);

	hidePlanets(planetSplitIndex, planetSplitIndex, duration);
	hideStandardButtons(duration);
}

void SceneMenu::hideCredits()
{
	if (getState() != SceneMenu::State::CREDITS)
		return;

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	scheduleEvent(duration, [this]()
	{
	});
	this->setState(SceneMenu::State::STANDARD);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_CHOOSE_INFO);

	showPlanets(planetSplitIndex, planetSplitIndex, duration);
	showStandardButtons(duration);
}

void SceneMenu::showOptions()
{
	if (isAnyPlanetFocused() || getState() == SceneMenu::State::OPTIONS)
		return;

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	scheduleEvent(duration, [this]()
	{
	});
	this->setState(SceneMenu::State::OPTIONS);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_BUTTON_NAMES[SceneMenu::BTN_OPTIONS]);

	hidePlanets(planetSplitIndex, planetSplitIndex, duration);
	hideStandardButtons(duration);
}

void SceneMenu::hideOptions()
{
	if (getState() != SceneMenu::State::OPTIONS)
		return;

	constexpr float duration = 0.6f;
	constexpr std::size_t planetSplitIndex = 3;

	scheduleEvent(duration, [this]()
	{
	});
	this->setState(SceneMenu::State::STANDARD);

	lbls[SceneMenu::LBL_MAIN_INFO].setText(SceneMenu::STR_CHOOSE_INFO);

	showPlanets(planetSplitIndex, planetSplitIndex, duration);
	showStandardButtons(duration);
}

void SceneMenu::hidePlanets(std::size_t leftSplitIndex, std::size_t rightSplitIndex, float duration)
{
	// hide tr1a
	imgTrappist1a.addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(-planet_offset_x(), imgTrappist1a.getPosition().y), duration));

	// hide left planets
	for (std::size_t i = 0; i < leftSplitIndex; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i] - planet_offset_x(), planet_y()), duration));

	// hide right planets
	for (std::size_t i = rightSplitIndex; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i] + planet_offset_x(), planet_y()), duration));
}

void SceneMenu::showPlanets(std::size_t leftSplitIndex, std::size_t rightSplitIndex, float duration)
{
	// show tr1a
	imgTrappist1a.addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(0.0f, imgTrappist1a.getPosition().y), duration));

	// show left planets
	for (std::size_t i = 0; i < leftSplitIndex; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i], planet_y()), duration));

	// show right planets
	for (std::size_t i = rightSplitIndex; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
		imgPlanets[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(planetXPositions[i], planet_y()), duration));
}

void SceneMenu::hideStandardButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(button_hidden_x(), button_base_y() - button_offset_y() * i), duration));
}

void SceneMenu::showStandardButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(button_shown_x(), button_base_y() - button_offset_y() * i), duration));
}

void SceneMenu::hidePlayButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(button_hidden_x(), button_base_y() - button_offset_y() * (i - SceneMenu::BTN_PLAY_BEGIN)), duration));
}

void SceneMenu::showPlayButtons(float duration)
{
	for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
		btns[i].addAction(ui::Vec2Action(ui::Vec2Action::MOVE_TO, glm::vec2(button_shown_x(), button_base_y() - button_offset_y() * (i - SceneMenu::BTN_PLAY_BEGIN)), duration));
}

void SceneMenu::onSizeChanged(unsigned int width, unsigned int height)
{
	this->widthf = static_cast<float>(width);
	this->heightf = static_cast<float>(height);

	/* objects */

	FloatRect rect = imgTrappist1a.getTextureRect();
	imgTrappist1a.setSize(((rect.width * imgTrappist1a.getTexture()->getSize().x) / (rect.height * imgTrappist1a.getTexture()->getSize().y)) * heightf, this->height());
	imgTrappist1a.setOrigin(0.0f, this->height() * 0.5f);
	imgTrappist1a.setPosition(0.0f, this->height() * 0.5f);

	constexpr float objectHeightMultiplicator = 0.15f;

	if (getState() == SceneMenu::State::STANDARD) // reset planet position
	{
		for (std::size_t i = 0; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
		{
			rect = imgPlanets[i].getTextureRect();
			imgPlanets[i].setSize(((rect.width * imgPlanets[i].getTexture()->getSize().x) / (rect.height * imgPlanets[i].getTexture()->getSize().y)) * (this->height() * objectHeightMultiplicator), this->height() * objectHeightMultiplicator);
			imgPlanets[i].setOrigin(imgPlanets[i].getSize() * 0.5f);
			planetXPositions[i] = this->width() * (static_cast<float>(i) * 0.1f + 0.23f);
			imgPlanets[i].setPosition(planetXPositions[i], planet_y());
		}
	}
	else // reset planet position plus offset
	{
		for (std::size_t i = 0; i < SceneMenu::IMG_PLANETS_SIZE; ++i)
		{
			rect = imgPlanets[i].getTextureRect();
			imgPlanets[i].setSize(((rect.width * imgPlanets[i].getTexture()->getSize().x) / (rect.height * imgPlanets[i].getTexture()->getSize().y)) * (this->height() * objectHeightMultiplicator), this->height() * objectHeightMultiplicator);
			imgPlanets[i].setOrigin(imgPlanets[i].getSize() * 0.5f);
			planetXPositions[i] = this->width() * (static_cast<float>(i) * 0.1f + 0.23f);
		}
		if (isAnyPlanetFocused()) // split on focused
		{
			hidePlanets(focusedPlanet, focusedPlanet + 1, 0.0f); // TODO: find better fix than duration 0.0f
			imgPlanets[focusedPlanet].setPosition(planet_focused_x(), planet_focused_y()); // move focussed planet to correct position
		}
		else // split default
		{
			hidePlanets(3, 3, 0.0f); // TODO: find better fix than duration 0.0f
		}
	}
	// TODO: fix standard button comeback when options or credits state and window is resized
	if (isAnyPlanetFocused()) // play buttons shown
	{
		for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
			btns[i].setPosition(button_hidden_x(), button_base_y() - button_offset_y() * i);
		for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
			btns[i].setPosition(button_shown_x(), button_base_y() - button_offset_y() * (i - SceneMenu::BTN_PLAY_BEGIN));

		// player
		imgPlayer.setPosition(player_focused_x(), player_focused_y());
	}
	else // standard buttons shown
	{
		for (std::size_t i = SceneMenu::BTN_STD_BEGIN; i < SceneMenu::BTN_STD_END; ++i)
			btns[i].setPosition(button_shown_x(), button_base_y() - button_offset_y() * i);
		for (std::size_t i = SceneMenu::BTN_PLAY_BEGIN; i < SceneMenu::BTN_PLAY_END; ++i)
			btns[i].setPosition(button_hidden_x(), button_base_y() - button_offset_y() * (i - SceneMenu::BTN_PLAY_BEGIN));

		// player
		imgPlayer.setPosition(half_width(), half_height());
	}
	imgPlayer.setSize(glm::vec2(imgTrappist1a.getSize().x * 0.1f, imgTrappist1a.getSize().x * 0.2f));
	imgPlayer.setOrigin(imgPlayer.getSize() * 0.5f);

	lbls[SceneMenu::LBL_TITLE].setPosition(0.0f, this->height() * 0.01f);
	lbls[SceneMenu::LBL_TITLE].setSize(this->width(), 0.0f);

	lbls[SceneMenu::LBL_MAIN_INFO].setPosition(0.0f, this->height() * 0.16f);
	lbls[SceneMenu::LBL_MAIN_INFO].setSize(this->width(), 0.0f);

	lbls[SceneMenu::LBL_PLANET_INFO].setPosition(half_width(), this->height() * 0.6f);
	lbls[SceneMenu::LBL_PLANET_INFO].setOrigin(half_width() * 0.6f, 0.0f);
	lbls[SceneMenu::LBL_PLANET_INFO].setSize(this->width() * 0.6f, 0.0f);

	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setPosition(this->width() * 0.8f, this->height() * 0.3f);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setSize(this->width() * 0.6f, 0.0f);
	lbls[SceneMenu::LBL_PLANET_PLAY_INFO].setOrigin(half_width() * 0.3f, 0.0f);
}