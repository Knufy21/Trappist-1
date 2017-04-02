#include <Trappist-1\scenes\SceneMenu.hpp>

#include <Trappist-1\Core.hpp>

#include <Trappist-1\ui\Listeners.hpp>
#include <Trappist-1\ui\Actions.hpp>

constexpr float buttonHightlightTime = 0.06f;

SceneMenu::SceneMenu()
{
	type = (SceneType::MENU);

	lblTitle.setFont(Core::font);
	lblTitle.setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	lblTitle.setTextThickness(0.05f);
	lblTitle.setTextOutlineThickness(0.2f);
	lblTitle.setTextOutlineColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	lblTitle.setFontSize(60);
	lblTitle.setTextAligment(ui::Label::Alignment::CENTER);
	lblTitle.setText("Trappist-1");
	lblTitle.setOrigin(200.0f, 0.0f);
	lblTitle.setSize(400.0f, 0.0f);
	lblTitle.setAutoSizeMode(ui::Label::AutoSizeMode::Y);

	addWidget(&lblTitle);

	/* btnPlay */
	btnPlay.setEventReceiver(true);
	btnPlay.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	btnPlay.setSize(glm::vec2(200.0f, 50.0f));
	btnPlay.setOrigin(100.0f, 25.0f);
	btnPlay.setFont(Core::font);
	btnPlay.setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	btnPlay.setFontSize(32);
	btnPlay.setTextAligment(ui::Label::Alignment::CENTER);
	btnPlay.setText("Spielen");
	btnPlay.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->btnPlay.setColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		}
		else
		{
			this->btnPlay.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
			Core::queryScene(SceneType::GAME);
		}
	}));
	btnPlay.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->btnPlay.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
		}
		else
		{
			this->btnPlay.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
		}
	}));
	addWidget(&btnPlay);

	/* btnOptions */
	btnOptions.setEventReceiver(true);
	btnOptions.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	btnOptions.setSize(glm::vec2(200.0f, 50.0f));
	btnOptions.setOrigin(100.0f, 25.0f);
	btnOptions.setFont(Core::font);
	btnOptions.setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	btnOptions.setFontSize(32);
	btnOptions.setTextAligment(ui::Label::Alignment::CENTER);
	btnOptions.setText("Optionen");
	btnOptions.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->btnOptions.setColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		}
		else
		{
			this->btnOptions.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}));
	btnOptions.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->btnOptions.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
		}
		else
		{
			this->btnOptions.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
		}
	}));
	addWidget(&btnOptions);

	/* btnExit */
	btnExit.setEventReceiver(true);
	btnExit.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	btnExit.setSize(glm::vec2(200.0f, 50.0f));
	btnExit.setOrigin(100.0f, 25.0f);
	btnExit.setFont(Core::font);
	btnExit.setTextColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	btnExit.setFontSize(32);
	btnExit.setTextAligment(ui::Label::Alignment::CENTER);
	btnExit.setText("Beenden");
	btnExit.addListener(ui::MouseButtonListener([this](const void *args)
	{
		const ui::MouseButtonEventArgs *e = static_cast<const ui::MouseButtonEventArgs *>(args);
		if (e->pressed)
		{
			this->btnExit.setColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
		}
		else
		{
			this->btnExit.setColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		}
	}));
	btnExit.addListener(ui::CursorEnterListener([this](const void *args)
	{
		const ui::CursorEnterEventArgs *e = static_cast<const ui::CursorEnterEventArgs *>(args);
		if (e->entered)
		{
			this->btnExit.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.1f, 1.1f), buttonHightlightTime));
		}
		else
		{
			this->btnExit.addAction(ui::Vec2Action(ui::Vec2Action::Type::SCALE_TO, glm::vec2(1.0f, 1.0f), buttonHightlightTime));
		}
	}));
	addWidget(&btnExit);

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

	btnPlay.setPosition(widthh, heighth - 60);
	btnOptions.setPosition(widthh, heighth);
	btnExit.setPosition(widthh, heighth + 60);

	lblTitle.setPosition(widthh, 10.0f);
}