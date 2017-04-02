#include <Trappist-1\CollisionDetector.hpp>
#include <Trappist-1\World.hpp>
#include <Trappist-1\entities\Entity.hpp>
#include <Trappist-1\components\Collider.hpp>

#include <SFML\Graphics.hpp>

namespace CollisionDetector
{

	void checkCollisions(Collider *collider, std::vector<Collider*> &v)
	{
		for (auto entity : World::entities)
		{
			if (entity->hasComponent(ComponentType::COLLIDER))
			{
				Collider *check = dynamic_cast<Collider*>(entity->getComponent(ComponentType::COLLIDER));
				if (check != collider)
				{
					if (check->getReach() + collider->getReach() > glm::length(check->getPosition() - collider->getPosition()))
					{
						if (doCollide(check, collider))
						{
							v.push_back(check);
						}
					}
				}
			}
		}
	}

	bool ccCollision(Collider *circle1, Collider *circle2)
	{
		return glm::length(circle1->getPosition() - circle2->getPosition()) < circle1->getRadius() + circle2->getRadius();
	}

	bool pointInCircle(glm::vec2 &point, glm::vec2 &circle, float radius)
	{
		return glm::length(point - circle) < radius;
	}

	bool crCollision(Collider *circle, Collider *rect)
	{
		glm::vec2 &c = circle->getPosition();
		glm::vec2 &r = rect->getPosition();
		glm::vec2 &s = rect->getSize() * 0.5f;

		if (c.x > r.x - s.x && c.x < r.x + s.x)
		{
			return circle->getRadius() + s.y > glm::abs(r.y - c.y);
		}

		if (c.y > r.y - s.y && c.y < r.y + s.y )
		{
			return circle->getRadius() + s.x > glm::abs(r.x - c.x);
		}

		if (pointInCircle(glm::vec2(r.x - s.x, r.y - s.y), c, circle->getRadius()))
		{
			return true;
		}

		if (pointInCircle(glm::vec2(r.x - s.x, r.y + s.y), c, circle->getRadius()))
		{
			return true;
		}

		if (pointInCircle(glm::vec2(r.x + s.x, r.y + s.y), c, circle->getRadius()))
		{
			return true;
		}

		if (pointInCircle(glm::vec2(r.x + s.x, r.y - s.y), c, circle->getRadius()))
		{
			return true;
		}

		return false;
		
	}

	bool rrCollision(Collider *rect1, Collider *rect2)
	{
		glm::vec2 &p1 = rect1->getPosition() - rect1->getSize() * 0.5f;
		glm::vec2 &p2 = rect2->getPosition() - rect2->getSize() * 0.5f;
		glm::vec2 &s1 = rect1->getSize();
		glm::vec2 &s2 = rect2->getSize();

		return (p1.x < p2.x + s2.x && p2.x < p1.x + s1.x && p1.y < p2.y + s2.y && p2.y < p1.y + s1.y);
	}

	bool doCollide(Collider *collider1, Collider *collider2)
	{
		ColliderType ct1 = collider1->colliderType;
		ColliderType ct2 = collider2->colliderType;

		if (ct1 == ColliderType::CIRCLE)
		{
			if (ct2 == ColliderType::CIRCLE)
			{
				return ccCollision(collider1, collider2);
			}
			else
			{
				return crCollision(collider1, collider2);
			}
		}
		else
		{
			if (ct2 == ColliderType::CIRCLE)
			{
				return crCollision(collider2, collider1);
			}
			else
			{
				return rrCollision(collider1, collider2);
			}
		}
		return false;
	}

}