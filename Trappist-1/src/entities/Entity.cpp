#include <Trappist-1\Entities\Entity.hpp>
#include <Trappist-1\Components.hpp>
#include <Trappist-1\Graphics\Renderer2D.hpp>
#include <Trappist-1\World.hpp>

#include <iostream>

Entity::Entity()
	: texture(nullptr), dead(false)
{
	setTextureRect(0.0f, 0.0f, 1.0f, 1.0f);
	setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	setLookDirection(glm::vec2(0, 1));
}

Entity::~Entity()
{
	for (size_t i = 0; i < ComponentType::COMPONENTCOUNT; ++i)
	{
		delete components[i];
	}
}

void Entity::update()
{
	for (size_t i = 0; i < ComponentType::COMPONENTCOUNT; ++i)
	{
		if(components[i] != nullptr)
		{
			components[i]->update();
		}
	}
}

void Entity::render(Renderer2D &renderer2d)
{
	renderer2d.pushMatrix(getTransform());
	renderer2d.submit4(vertices, texture, getPosition().y / -World::HALF_HEIGHT_F);
	renderer2d.popMatrix();
}

void Entity::destroy()
{
	dead = true;
}

void Entity::setColor(const glm::vec4 &color)
{
	vertices[0].color = color;
	vertices[1].color = color;
	vertices[2].color = color;
	vertices[3].color = color;
}

void Entity::setTexture(const Texture *texture)
{
	this->texture = texture;
}

void Entity::setLookDirection(const glm::vec2 &direction)
{
	lookDirection = direction;
}

void Entity::setTextureRect(const FloatRect &textureRect)
{
	vertices[0].texCoord.x = textureRect.left;
	vertices[0].texCoord.y = textureRect.top;

	vertices[2].texCoord.x = textureRect.left + textureRect.width;
	vertices[2].texCoord.y = textureRect.top + textureRect.height;

	vertices[1].texCoord.x = textureRect.left;
	vertices[1].texCoord.y = textureRect.top + textureRect.height;

	vertices[3].texCoord.x = textureRect.left + textureRect.width;
	vertices[3].texCoord.y = textureRect.top;
}

void Entity::setTextureRect(float left, float top, float width, float height)
{
	vertices[0].texCoord.x = left;
	vertices[0].texCoord.y = top;

	vertices[2].texCoord.x = left + width;
	vertices[2].texCoord.y = top + height;

	vertices[1].texCoord.x = left;
	vertices[1].texCoord.y = top + height;

	vertices[3].texCoord.x = left + width;
	vertices[3].texCoord.y = top;
}

void Entity::setSize(const glm::vec2 &size)
{
	vertices[3].position.x = size.x;

	vertices[1].position.y = size.y;

	vertices[2].position.x = size.x;
	vertices[2].position.y = size.y;
}

bool Entity::move(const glm::vec2 &movement)
{
	bool f = true;

	for (int i = 0; i < ComponentType::COMPONENTCOUNT; i++)
	{
		if (hasComponent(ComponentType(i)))
		{
			if (!components[i]->canMove(movement))
			{
				f = false;
			}
		}
	}

	if (f)
	{
		translate(movement);

		for (int i = 0; i < ComponentType::COMPONENTCOUNT; i++)
		{
			if (hasComponent(ComponentType(i)))
			{
				components[i]->onMove(movement);
			}
		}
	}

	return f;
}

bool Entity::onCollision(Collider *other)
{
	bool f = true;

	for (int i = 0; i < ComponentType::COMPONENTCOUNT; i++)
	{
		if (hasComponent(ComponentType(i)))
		{
			if (!components[i]->onCollision(other))
			{
				f = false;
			}
		}
	}

	return f;
}

void Entity::addComponent(Component *component)
{
	components[component->type] = component;
}

void Entity::removeComponent(ComponentType cType)
{
	components[cType] = nullptr;
}

bool Entity::hasComponent(ComponentType cType)
{
	return components[cType] != nullptr;
}

Component* Entity::getComponent(ComponentType cType)
{
	return components[cType];
}