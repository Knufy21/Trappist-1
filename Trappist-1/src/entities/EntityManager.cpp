#include <Trappist-1\entities\EntityManager.h>

namespace EntityManager
{
	Entity* createEntity(EntityType type)
	{
		switch (type)
		{

		default:
			return nullptr;
		}
	}

	Entity* createProjectile(Entity *entity, glm::vec2 direction, float damage)
	{
		return entity;
	}
}