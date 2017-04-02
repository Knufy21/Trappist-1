#include <Trappist-1\graphics\Transform2D.hpp>

#include "glm\gtx\matrix_transform_2d.hpp"

Transform2D::Transform2D(const glm::vec2 &position, float rotation, const glm::vec2 &scalar, const glm::vec2 &origin)
	: position(position), rotation(rotation), scalar(scalar), origin(origin)
{	}

Transform2D::~Transform2D()
{	}

const glm::mat3 &Transform2D::getTransform() const
{
	ensureUpdate();
	return transform;
}

void Transform2D::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;

	this->needsUpdate = true;
}

void Transform2D::setPosition(const glm::vec2 &position)
{
	this->position.x = position.x;
	this->position.y = position.y;

	this->needsUpdate = true;
}

void Transform2D::translate(float offsetX, float offsetY)
{
	this->position.x += offsetX;
	this->position.y += offsetY;

	this->needsUpdate = true;
}

void Transform2D::translate(const glm::vec2 &offset)
{
	this->position.x += offset.x;
	this->position.y += offset.y;

	this->needsUpdate = true;
}

void Transform2D::setOrigin(float originX, float originY)
{
	this->origin.x = originX;
	this->origin.y = originY;

	this->needsUpdate = true;
}

void Transform2D::setOrigin(const glm::vec2 &origin)
{
	this->origin.x = origin.x;
	this->origin.y = origin.y;

	this->needsUpdate = true;
}

void Transform2D::setRotation(float rotation)
{
	this->rotation = rotation;

	this->needsUpdate = true;
}

void Transform2D::rotate(float angle)
{
	this->rotation += angle;

	this->needsUpdate = true;
}

void Transform2D::setScale(float scalarX, float scalarY)
{
	this->scalar.x = scalarX;
	this->scalar.y = scalarY;

	this->needsUpdate = true;
}

void Transform2D::setScale(const glm::vec2 &scale)
{
	this->scalar.x = scale.x;
	this->scalar.y = scale.y;

	this->needsUpdate = true;
}

void Transform2D::scale(float factorX, float factorY)
{
	this->scalar.x *= factorX;
	this->scalar.y *= factorY;

	this->needsUpdate = true;
}

void Transform2D::scale(const glm::vec2 &factors)
{
	this->scalar.x *= factors.x;
	this->scalar.y *= factors.y;

	this->needsUpdate = true;
}

glm::vec2 Transform2D::transformPoint(float x, float y) const
{
	return glm::vec2(getTransform() * glm::vec3(x, y, 1.0f));
}

glm::vec2 Transform2D::transformPoint(const glm::vec2 &point) const
{
	return glm::vec2(getTransform() * glm::vec3(point.x, point.y, 1.0f));
}

sf::FloatRect Transform2D::transformRect(float left, float top, float width, float height) const
{
	glm::vec2 tl = transformPoint(left, top);
	glm::vec2 br = transformPoint(left + width, top + height);
	return sf::FloatRect(tl.x, tl.y, br.x, br.y);
}

sf::FloatRect Transform2D::transformRect(const sf::FloatRect &rect) const
{
	glm::vec2 tl = transformPoint(rect.left, rect.top);
	glm::vec2 br = transformPoint(rect.left + rect.width, rect.top + rect.height);
	return sf::FloatRect(tl.x, tl.y, br.x - tl.x, br.y - tl.y);
}

void Transform2D::ensureUpdate() const
{
	if (this->needsUpdate)
	{
		// Update
		this->transform = glm::translate(glm::mat3(), getPosition());
		this->transform = glm::rotate(this->transform, getRotation());
		this->transform = glm::scale(this->transform, getScale());
		this->transform = glm::translate(this->transform, -getOrigin());

		// Mark as updated
		this->needsUpdate = false;
	}
}