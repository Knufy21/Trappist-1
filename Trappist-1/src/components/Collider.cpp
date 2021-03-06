#include <Trappist-1\Components\Collider.hpp>
#include <Trappist-1\Entities\Entity.hpp>
#include <Trappist-1\CollisionDetector.hpp>

Collider::Collider(Entity *entity, float radius) : Component(entity)
{
	this->type = ComponentType::COLLIDER;
	this->colliderType = ColliderType::CIRCLE;
	this->radius = radius;
	this->reach = radius;
}

Collider::Collider(Entity *entity, glm::vec2 &size) : Component(entity)
{
	this->type = ComponentType::COLLIDER;
	this->colliderType = ColliderType::RECT;
	this->size = size;
	this->reach = glm::length(size) / 2;
}

void Collider::update()
{
	position = entity->getPosition();
}

void Collider::onMove(const glm::vec2 &movement)
{
	position = entity->getPosition();
}

bool Collider::canMove(const glm::vec2 &movement)
{
	bool f = true;

	position += movement;
	std::vector<Collider*> collisions;
	CollisionDetector::checkCollisions(this, collisions);

	for (auto c : collisions)
	{
		if (!c->entity->onCollision(this))
		{
			f = false;
		}
	}

	position -= movement;
	
	return f;
}
