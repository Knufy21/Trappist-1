#include <Trappist-1\components\Movement.hpp>
#include <Trappist-1\entities\Entity.hpp>
#include <Trappist-1\util\Time.hpp>
#include <Trappist-1\components\Animator.hpp>

Movement::Movement(Entity *entity) : Component(entity)
{
	type = ComponentType::MOVEMENT;
	friction = 100;
	maxSpeed = 10;
	stop = true;
}

void Movement::update()
{
	float factor = Time::deltaTime * friction;
	if (!stop)
	{
		if (glm::length(desiredDirection * maxSpeed - velocity) <= factor)
		{
			velocity = desiredDirection * maxSpeed;
		}
		else
		{
			velocity += glm::normalize(desiredDirection * maxSpeed - velocity) * factor;
		}
	}
	else
	{
		if (glm::length(velocity) <= factor)
		{
			velocity = glm::vec2(0, 0);
		}
		else
		{
			velocity -= glm::normalize(velocity) * factor;
		}
	}

	if (!entity->move(glm::vec2(velocity.x, 0)))
	{
		velocity.x = 0;
	}
	else
	{

	}

	if (!entity->move(glm::vec2(0, velocity.y)))
	{
		velocity.y = 0;
	}
	else
	{

	}
}

void Movement::setDesiredDirection(float angle)
{
	desiredDirection = glm::vec2(glm::cos(glm::radians(angle)), glm::sin(glm::radians(angle)));
	stop = false;
}

void Movement::setDesiredDirection(const glm::vec2 &direction)
{
	glm::vec2 newDirection = glm::normalize(direction);
	if (newDirection != desiredDirection || stop)
	{
		if (entity->hasComponent(ComponentType::ANIMATOR))
		{
			if (newDirection.x > 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("MoveRight");
			else if (newDirection.x < 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("MoveLeft");

			bool walkY = true;
			if (newDirection.y > 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("MoveFront");
			else if (newDirection.y < 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("MoveBack");				
		}
	}
	desiredDirection = newDirection;

	stop = false;
}

void Movement::desireStop()
{
	stop = true;

	if (glm::length(velocity) > 0)
	{
		if (entity->hasComponent(ComponentType::ANIMATOR))
		{
			if (desiredDirection.x > 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("IdleRight");
			else if (desiredDirection.x < 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("IdleLeft");

			bool walkY = true;
			if (desiredDirection.y > 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("IdleFront");
			else if (desiredDirection.y < 0.0f)
				static_cast<Animator *>(entity->getComponent(ComponentType::ANIMATOR))->setAnimationByName("IdleBack");
		}
	}
}