#include <Trappist-1\ui\widgets\CheckButton.hpp>

#include <Trappist-1\ui\widgets\CheckButtonGroup.hpp>

#include <Trappist-1\Graphics\Renderer2D.hpp>

namespace ui
{
	CheckButton::CheckButton()
		: BASE()
	{  }

	CheckButton::~CheckButton()
	{  }

	bool CheckButton::isChecked() const
	{
		return checked;
	}

	void CheckButton::setChecked(bool checked)
	{
		this->checked = checked;

		if (checkButtonGroup != nullptr)
			checkButtonGroup->onCheckButtonCheckChanged(*this);
	}

	void CheckButton::setCheckmarkTexture(const Texture &texture, bool resetCheckmarkSize)
	{
		this->texCheckmark = &texture;
	
		checkmarkVertices[1].texCoord.y = static_cast<float>(texture.getSize().y);
		checkmarkVertices[2].texCoord.x = static_cast<float>(texture.getSize().x);
		checkmarkVertices[3].texCoord.x = static_cast<float>(texture.getSize().x);
		checkmarkVertices[3].texCoord.y = static_cast<float>(texture.getSize().y);
	
		if (resetCheckmarkSize)
			setCheckmarkSize(glm::vec2(texture.getSize().x, texture.getSize().y));
	}
	
	const Texture& CheckButton::getCheckmarkTexture() const
	{
		return *texCheckmark;
	}
	
	void CheckButton::setCheckmarkSize(const glm::vec2 &size)
	{
		checkmarkVertices[1].position.y = size.y;
		checkmarkVertices[2].position.x = size.x;
		checkmarkVertices[3].position.x = size.x;
		checkmarkVertices[3].position.y = size.y;
	
		//updateCheckmarkPosition();
	}
	
	const glm::vec2 &CheckButton::getCheckmarkSize() const
	{
		return checkmarkVertices[2].position;
	}
	
	void CheckButton::setCheckmarkColor(const glm::vec4 &color)
	{
		checkmarkVertices[0].color = color;
		checkmarkVertices[1].color = color;
		checkmarkVertices[2].color = color;
		checkmarkVertices[3].color = color;
	}
	
	const glm::vec4& CheckButton::getCheckmarkColor() const
	{
		return checkmarkVertices[0].color;
	}
	
	//void CheckButton::updatePosition()
	//{
	//	updateCheckmarkPosition();
	//}
	//
	//void CheckButton::resetCheckmarkPosition()
	//{
	//	sf::Vector2f checkmarkSize = getCheckmarkSize();
	//	float yTop = getLocalBounds().height * .5f + checkmarkSize.y * .5f;
	//	float yBottom = getLocalBounds().height * .5f - checkmarkSize.y * .5f;
	//
	//	checkmarkVertices[0].position.y = yTop;
	//	checkmarkVertices[2].position.y = yTop;
	//	checkmarkVertices[1].position.y = yBottom;
	//	checkmarkVertices[3].position.y = yBottom;
	//
	//	float xLeft = getLocalBounds().width * .5f + checkmarkSize.x * .5f;
	//	float xRight = getLocalBounds().width * .5f - checkmarkSize.x * .5f;
	//
	//	checkmarkVertices[0].position.x = xLeft;
	//	checkmarkVertices[1].position.x = xLeft;
	//	checkmarkVertices[2].position.x = xRight;
	//	checkmarkVertices[3].position.x = xRight;
	//}
	//
	//void CheckButton::updateCheckmarkPosition()
	//{
	//	resetCheckmarkPosition();
	//}
	//
	//void CheckButton::onMouseButtonPressed(sf::Mouse::Button button, const sf::Vector2f &mousePosRelTopLeft)
	//{
	//	BASE::onMouseButtonPressed(button, mousePosRelTopLeft);
	//
	//	if (enabled)
	//		setChecked(!checked);
	//}

	void CheckButton::performSubmittion(Renderer2D &renderer2d) const
	{
		BASE::performSubmittion(renderer2d);
		
		if (checked)
			renderer2d.submit4(checkmarkVertices, texCheckmark);
	}
}