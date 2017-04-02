#include <Trappist-1\components\Health.hpp>
#include <Trappist-1\entities\Entity.hpp>

Health::Health(int maxHp, Entity *entity) : Component(entity)
{
	type = ComponentType::HEALTH;
	this->maxHp = maxHp;
	this->hp = maxHp;
}

void Health::damage(int dmg)
{
	hp -= dmg;
	if (hp <= 0) {
		entity->onDeath();
	}
}