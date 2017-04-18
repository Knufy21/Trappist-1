#pragma once

#include <Trappist-1\graphics\Transform2D.hpp>
#include <Trappist-1\graphics\Texture.hpp>
#include <Trappist-1\graphics\Vertex2D.hpp>
#include <Trappist-1\components\Component.hpp>

class Renderer2D;

class Entity : public Transform2D
{
public:
	Entity();
	virtual ~Entity();

	// Updates all the Components of the Entity.
	virtual void update();

	// Renedrs the Entity if it has a Sprite.
	void render(Renderer2D &renderer2d);

	// Destroys the Entity.
	void destroy();

	// Returns whether the Entity is marked as dead.
	bool isDead() const;

	// Returns the color of the entity.
	const glm::vec4 &getColor() const;

	// Sets the color of the entity.
	void setColor(const glm::vec4 &color);

	// Return the size of the entity.
	const glm::vec2 &getSize() const;

	// Sets the size of the entity.
	void setSize(const glm::vec2 &size);

	// Returns the texture of the entity. If the entity doesn't have a texture nullptr is returned.
	const Texture *getTexture() const;

	// Sets the texture of the entity.
	void setTexture(const Texture *texture);

	// Returns the texture rect of the entity with the values ranging from 0.0f to 1.0f.
	FloatRect getTextureRect() const;

	// Sets the texture rect of the entity  with the values ranging from 0.0f to 1.0f.
	void setTextureRect(const FloatRect &textureRect);

	// Sets the texture rect of the entity  with the values ranging from 0.0f to 1.0f.
	void setTextureRect(float left, float top, float width, float height);

	// Returns the direction the entity is looking in.
	const glm::vec2 &getLookDirection() const;

	// Sets the direction the entity is looking in.
	void setLookDirection(const glm::vec2 &direction);

	// Adds a component to the Entity or overrides the old component od this type.
	void addComponent(Component *component);

	// Removes the Component of the given type.
	void removeComponent(ComponentType cType);

	// Returns true if the Entity has the given Component.
	bool hasComponent(ComponentType cType);

	// Returns the Component if there is one of that type.
	Component* getComponent(ComponentType cType);

	// Tries to move the entity by the given vec2 and returns whether it was successful.
	bool move(const glm::vec2 &movement);

	// Gets called when the entitys health reaches 0.
	void onDeath() {}

	// Gets called when the entitys collides and returns whether it cann pass.
	bool onCollision(Collider *other);

private:
	Component* components[ComponentType::COMPONENTCOUNT];
	bool dead;

	// °0  °3
	// °1  °2
	VertexPCT2D vertices[4];

	const Texture *texture;
	glm::vec2 lookDirection;
};

// Inline

inline const glm::vec4 &Entity::getColor() const
{
	return this->vertices[0].color;
}

inline const glm::vec2 &Entity::getSize() const
{
	return this->vertices[2].position;
}

inline const glm::vec2& Entity::getLookDirection() const
{
	return this->lookDirection;
}

inline const Texture *Entity::getTexture() const
{
	return this->texture;
}

inline FloatRect Entity::getTextureRect() const
{
	return FloatRect(vertices[0].texCoord.x, vertices[0].texCoord.y, vertices[2].texCoord.x, vertices[2].texCoord.y);
}

inline bool Entity::isDead() const
{
	return dead;
}

