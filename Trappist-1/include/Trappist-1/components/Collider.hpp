#pragma once

#include <Trappist-1\Components\Component.hpp>

enum ColliderType
{
	RECT,
	CIRCLE
};

class Collider : public Component
{
public:
	Collider(Entity *entity, float radius);
	Collider(Entity *entity, glm::vec2 &size);

	void update() override;
	void onMove(const glm::vec2 &movement) override;
	bool canMove(const glm::vec2 &movement) override;

	// Returns the position of the collider.
	glm::vec2 getPosition() const;

	// Returns the size of the collider.
	glm::vec2 getSize() const;

	// Returns the radius of the collider.
	float getRadius() const;

	// Returns the maximum length of the collider from its center.
	float getReach() const;

	ColliderType colliderType;
private:
	glm::vec2 position;
	float radius;
	glm::vec2 size;
	float reach;

};

inline glm::vec2 Collider::getPosition() const
{
	return position;
}

inline glm::vec2 Collider::getSize() const
{
	return size;
}

inline float Collider::getRadius() const
{
	return radius;
}

inline float Collider::getReach() const
{
	return reach;
}