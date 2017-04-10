#include <Trappist-1\scenes\SceneMenu.hpp>

#include <Trappist-1\Core.hpp>

#include <Trappist-1\ui\Listeners.hpp>
#include <Trappist-1\ui\Actions.hpp>
#include <Trappist-1\TextureManager.hpp>

constexpr float buttonHightlightTime = 0.06f;
constexpr float buttonPressTime = 0.06f;
constexpr float labelFadeInTime = 0.05f;
constexpr float labelFadeOutTime = 0.05f;


SceneMenu::SceneMenu()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	type = (Scene::Type::MENU);

	lblTitle.setFont(Core::font);
	lblTitle.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	lblTitle.setTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	lblTitle.setTextThickness(0.05f);
	lblTitle.setTextOutlineThickness(0.2f);
	lblTitle.setTextOutlineColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lblTitle.setFontSize(60);
	lblTitle.setTextAlignment(ui::Label::Alignment::CENTER);
	lblTitle.setText("Trappist-1");
	lblTitle.setOrigin(200.0f, 0.0f);
	lblTitle.setSize(400.0f, 0.0f);
	lblTitle.setAutoSizeMode(ui::Label::AutoSizeMode::Y);

	addWidget(&lblTitle);

	lblChooseInfo.setFont(Core::font);
	lblChooseInfo.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	lblChooseInfo.setTextColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	lblChooseInfo.setTextThickness(0.05f);
	lblChooseInfo.setTextOutlineThickness(0.1f);
	lblChooseInfo.setTextOutlineColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lblChooseInfo.setFontSize(40);
	lblChooseInfo.setTextAlignment(ui::Label::Alignment::CENTER);
	lblChooseInfo.setText("Choose a planet to play on.");
	lblChooseInfo.setAutoSizeMode(ui::Label::AutoSizeMode::Y);
	addWidget(&lblChooseInfo);

	/* objects */
	TextureManager::load(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS, "res/textures/system");
	TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->setSmooth(false);

	imgTrappist1a.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1a"));
	imgTrappist1a.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	
	addWidget(&imgTrappist1a);

	imgTrappist1b.setEventReceiver(true);
	imgTrappist1b.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1b"));
	imgTrappist1b.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1b.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1b.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 b\nOrbital period: 1.51 days\nDistance to star: 0.011 AU\nRadius: 1.09 earth radii\nMass: 0.85 earths");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1b.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));

			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1b.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1b.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1b.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1b);

	imgTrappist1c.setEventReceiver(true);
	imgTrappist1c.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1c"));
	imgTrappist1c.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1c.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1c.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 c\nOrbital period: 2.42 days\nDistance to star: 0.015 AU\nRadius: 1.06 earth radii\nMass: 1.38 earths");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1c.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1c.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1c.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1c.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1c);

	imgTrappist1d.setEventReceiver(true);
	imgTrappist1d.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1d"));
	imgTrappist1d.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1d.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1d.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 d\nOrbital period: 4.05 days\nDistance to star: 0.021 AU\nRadius: 0.77 earth radii\nMass: 0.41 earths");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1d.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1d.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1d.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1d.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1d);

	imgTrappist1e.setEventReceiver(true);
	imgTrappist1e.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1e"));
	imgTrappist1e.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1e.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1e.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 e\nOrbital period: 6.10 days\nDistance to star: 0.028 AU\nRadius: 0.92 earth radii\nMass: 0.62 earths");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1e.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1e.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1e.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1e.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1e);

	imgTrappist1f.setEventReceiver(true);
	imgTrappist1f.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1f"));
	imgTrappist1f.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1f.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1f.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 f\nOrbital period: 9.21 days\nDistance to star: 0.037 AU\nRadius: 1.04 earth radii\nMass: 0.68 earths");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1f.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1f.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1f.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1f.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1f);

	imgTrappist1g.setEventReceiver(true);
	imgTrappist1g.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1g"));
	imgTrappist1g.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1g.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1g.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 g\nOrbital period: 12.35 days\nDistance to star: 0.045 AU\nRadius: 1.13 earth radii\nMass: 1.34 earths");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1g.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1g.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1g.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1g.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1g);

	imgTrappist1h.setEventReceiver(true);
	imgTrappist1h.setTextureRect(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexCoord("Trappist-1h"));
	imgTrappist1h.setTexture(TextureManager::get(TextureManager::TextureHandles::TRAPPIST_1_SYSTEM_ATLAS)->getTexture(), false);
	imgTrappist1h.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->imgTrappist1h.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));

			this->lblPlanetInfo.setText("Trappist-1 h\nOrbital period: ~20 days\nDistance to star: ~0.06 AU\nRadius: 0.76 earth radii\nMass: ?");
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), labelFadeInTime));
		}
		else
		{
			this->imgTrappist1h.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
			this->lblPlanetInfo.addAction(ui::Vec4Action(ui::Vec4Action::Type::TEXT_RGBA_TO, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), labelFadeOutTime));
		}
	}));
	imgTrappist1h.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->imgTrappist1h.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.05f, 1.05f), buttonPressTime));
		}
		else
		{
			this->imgTrappist1h.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonPressTime));

			Core::queryScene(Scene::Type::GAME);
		}
	}));
	addWidget(&imgTrappist1h);

	/* info labels*/

	#define labelColorDefault glm::vec4(0.9f, 0.9f, 1.0f, 0.2f)
	#define labelSize glm::vec2(200.0f, 50.0f)
	#define labelOrigin glm::vec2(100.0f, 25.0f)
	#define labelTextColor glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	#define labelOutlineColor glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)
	#define labelFontSize 20u
	#define labelFont Core::font
	#define labelTextThickness 0.0f
	#define labelOutlineThickness 0.0f
	#define labelTextAlignment ui::Label::Alignment::LEFT
	#define labelAutoSizeMode ui::Label::AutoSizeMode::NONE

	lblPlanetInfo.setFont(labelFont);
	lblPlanetInfo.setColor(labelColorDefault);
	lblPlanetInfo.setTextColor(labelTextColor);
	lblPlanetInfo.setTextThickness(labelTextThickness);
	lblPlanetInfo.setTextOutlineThickness(labelOutlineThickness);
	lblPlanetInfo.setTextOutlineColor(labelOutlineColor);
	lblPlanetInfo.setFontSize(labelFontSize);
	lblPlanetInfo.setTextAlignment(labelTextAlignment);
	//lblPlanetInfo.setText("Trappist-1 b\nMass: 0.85 earths");
	//lblPlanetInfo.setVisible(false);
	
	lblPlanetInfo.setAutoSizeMode(labelAutoSizeMode);
	addWidget(&lblPlanetInfo);

	/* buttons */
	
	#define buttonColorDefault glm::vec4(0.9f, 0.9f, 1.0f, 0.2f)
	#define buttonColorHighlighted glm::vec4(1.0f, 1.0f, 1.0f, 0.3f)
	#define buttonColorPressed glm::vec4(1.0f, 1.0f, 1.0f, 0.4f)
	#define buttonSize glm::vec2(200.0f, 50.0f)
	#define buttonOrigin glm::vec2(100.0f, 25.0f)
	#define buttonTextColor glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)
	#define buttonFontSize 32u
	#define buttonFont Core::font

	/* btnPlay */
	btnCredits.setEventReceiver(true);
	btnCredits.setColor(buttonColorDefault);
	btnCredits.setSize(buttonSize);
	btnCredits.setOrigin(buttonOrigin);
	btnCredits.setFont(buttonFont);
	btnCredits.setTextColor(buttonTextColor);
	btnCredits.setFontSize(buttonFontSize);
	btnCredits.setTextAlignment(ui::Label::Alignment::CENTER);
	//btnCredits.setAutoSizeMode(ui::Label::AutoSizeMode::Y);
	btnCredits.setText("Credits");
	btnCredits.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->btnCredits.setColor(buttonColorPressed);
		}
		else
		{
			this->btnCredits.setColor(buttonColorHighlighted);
		}
	}));
	btnCredits.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->btnCredits.setColor(buttonColorHighlighted);
			this->btnCredits.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
		}
		else
		{
			this->btnCredits.setColor(buttonColorDefault);
			this->btnCredits.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
		}
	}));
	addWidget(&btnCredits);

	/* btnOptions */
	btnOptions.setEventReceiver(true);
	btnOptions.setColor(buttonColorDefault);
	btnOptions.setSize(buttonSize);
	btnOptions.setOrigin(buttonOrigin);
	btnOptions.setFont(buttonFont);
	btnOptions.setTextColor(buttonTextColor);
	btnOptions.setFontSize(buttonFontSize);
	btnOptions.setTextAlignment(ui::Label::Alignment::CENTER);
	//btnOptions.setAutoSizeMode(ui::Label::AutoSizeMode::Y);
	btnOptions.setText("Options");
	btnOptions.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->btnOptions.setColor(buttonColorPressed);
		}
		else
		{
			this->btnOptions.setColor(buttonColorHighlighted);
		}
	}));
	btnOptions.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->btnOptions.setColor(buttonColorHighlighted);
			this->btnOptions.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
		}
		else
		{
			this->btnOptions.setColor(buttonColorDefault);
			this->btnOptions.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
		}
	}));
	addWidget(&btnOptions);

	/* btnExit */
	btnQuit.setEventReceiver(true);
	btnQuit.setColor(buttonColorDefault);
	btnQuit.setSize(buttonSize);
	btnQuit.setOrigin(buttonOrigin);
	btnQuit.setFont(buttonFont);
	btnQuit.setTextColor(buttonTextColor);
	btnQuit.setFontSize(buttonFontSize);
	btnQuit.setTextAlignment(ui::Label::Alignment::CENTER);
	//btnQuit.setAutoSizeMode(ui::Label::AutoSizeMode::Y);
	btnQuit.setText("Quit");
	btnQuit.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->btnQuit.setColor(buttonColorPressed);
		}
		else
		{
			this->btnQuit.setColor(buttonColorHighlighted);
			Core::exit();
		}
	}));
	btnQuit.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->btnQuit.setColor(buttonColorHighlighted);
			this->btnQuit.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
		}
		else
		{
			this->btnQuit.setColor(buttonColorDefault);
			this->btnQuit.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
		}
	}));
	addWidget(&btnQuit);

	onSizeChanged(Core::windowSize.x, Core::windowSize.y);
}

SceneMenu::~SceneMenu()
{

}

void SceneMenu::update()
{
	BASE::update();
}

void SceneMenu::render(Renderer2D &renderer2d)
{
	BASE::render(renderer2d);
}

void SceneMenu::onSizeChanged(unsigned int width, unsigned int height)
{
	float widthf = static_cast<float>(width);
	float heightf = static_cast<float>(height);

	float heighth = heightf * 0.5f;
	float widthh = widthf * 0.5f;
	float ratio = widthf / heightf;

	/* objects */

	FloatRect rect = imgTrappist1a.getTextureRect();
	imgTrappist1a.setSize(((rect.width * imgTrappist1a.getTexture()->getSize().x) / (rect.height * imgTrappist1a.getTexture()->getSize().y)) * heightf, heightf);

	constexpr float objectHeightMultiplicator = 0.15f;

	rect = imgTrappist1b.getTextureRect();
	imgTrappist1b.setSize(((rect.width * imgTrappist1b.getTexture()->getSize().x) / (rect.height * imgTrappist1b.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1b.setOrigin(imgTrappist1b.getSize() * 0.5f);
	imgTrappist1b.setPosition(widthf * 0.2f, heightf * 0.5f);

	rect = imgTrappist1c.getTextureRect();
	imgTrappist1c.setSize(((rect.width * imgTrappist1c.getTexture()->getSize().x) / (rect.height * imgTrappist1c.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1c.setOrigin(imgTrappist1c.getSize() * 0.5f);
	imgTrappist1c.setPosition(widthf * 0.32f, heightf * 0.5f);

	rect = imgTrappist1d.getTextureRect();
	imgTrappist1d.setSize(((rect.width * imgTrappist1d.getTexture()->getSize().x) / (rect.height * imgTrappist1d.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1d.setOrigin(imgTrappist1d.getSize() * 0.5f);
	imgTrappist1d.setPosition(widthf * 0.44f, heightf * 0.5f);

	rect = imgTrappist1e.getTextureRect();
	imgTrappist1e.setSize(((rect.width * imgTrappist1e.getTexture()->getSize().x) / (rect.height * imgTrappist1e.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1e.setOrigin(imgTrappist1e.getSize() * 0.5f);
	imgTrappist1e.setPosition(widthf * 0.56f, heightf * 0.5f);

	rect = imgTrappist1f.getTextureRect();
	imgTrappist1f.setSize(((rect.width * imgTrappist1f.getTexture()->getSize().x) / (rect.height * imgTrappist1f.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1f.setOrigin(imgTrappist1f.getSize() * 0.5f);
	imgTrappist1f.setPosition(widthf * 0.68f, heightf * 0.5f);

	rect = imgTrappist1g.getTextureRect();
	imgTrappist1g.setSize(((rect.width * imgTrappist1g.getTexture()->getSize().x) / (rect.height * imgTrappist1g.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1g.setOrigin(imgTrappist1g.getSize() * 0.5f);
	imgTrappist1g.setPosition(widthf * 0.8f, heightf * 0.5f);

	rect = imgTrappist1h.getTextureRect();
	imgTrappist1h.setSize(((rect.width * imgTrappist1h.getTexture()->getSize().x) / (rect.height * imgTrappist1h.getTexture()->getSize().y)) * (heightf * objectHeightMultiplicator), heightf * objectHeightMultiplicator);
	imgTrappist1h.setOrigin(imgTrappist1h.getSize() * 0.5f);
	imgTrappist1h.setPosition(widthf * 0.92f, heightf * 0.5f);

	btnCredits.setPosition(widthf * 0.8f, heightf * 0.8f - 60.0f);
	btnOptions.setPosition(widthf * 0.8f, heightf * 0.8f);
	btnQuit.setPosition(widthf * 0.8f, heightf * 0.8f + 60.0f);

	lblTitle.setPosition(widthh, heightf * 0.01f);

	lblChooseInfo.setPosition(widthh, lblTitle.getPosition().y + heightf * 0.15f);
	lblChooseInfo.setOrigin(widthh * 0.94f, 0.0f);
	lblChooseInfo.setSize(widthf * 0.94f, 0.0f);

	/*planet info*/

	lblPlanetInfo.setPosition(widthh, heightf * 0.6f);
	lblPlanetInfo.setOrigin(widthh * 0.6f, 0.0f);
	lblPlanetInfo.setSize(widthf * 0.6f, 0.0f);
}