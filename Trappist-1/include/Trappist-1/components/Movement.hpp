#pragma once

#include <Trappist-1\components\Component.hpp>
#include <glm\glm.hpp>

class Movement : public Component
{
	friend class SceneGame; // TODO: remove
public:
	Movement(Entity *entity);

	void update();

	// Sets the direction the entity will move to the given angle. 0 -> right; 90 -> down.
	void setDesiredDirection(float angle);

	void setDesiredDirection(const glm::vec2 &direction);

	// The entity will slow down until it stops.
	void desireStop();

private:
	glm::vec2 velocity;
	glm::vec2 desiredDirection;

	float maxSpeed;
	float friction;

	bool stop;

};