#pragma once

#include <Trappist-1\entities\Entity.hpp>

namespace EntityManager
{
	// Returns a new entity of the given type. Its not added to the world.
	Entity* createEntity(EntityType type);

	// Takes an entity and prepares it to be a projectile. Its not added to the world.
	Entity* createProjectile(Entity *entity, glm::vec2 direction, float damage);
}
