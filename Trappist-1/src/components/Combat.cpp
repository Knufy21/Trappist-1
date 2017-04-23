#include <Trappist-1\components\Combat.hpp>
#include <Trappist-1\util\Time.hpp>

Combat::Combat(Entity *entity, float attackSpeed, float damage) : Component(entity)
{
	this->type = ComponentType::COMBAT;
	this->attackSpeed = attackSpeed;
	this->damage = damage;
	this->melee = true;
	this->restCooldown = calcCooldown();
}

Combat::Combat(Entity *entity, float attackSpeed, float damage, Entity *projectile) : Component(entity)
{
	this->type = ComponentType::COMBAT;
	this->attackSpeed = attackSpeed;
	this->damage = damage;
	this->melee = false;
	this->restCooldown = calcCooldown();
	this->projectile = projectile;
}

Combat::~Combat()
{
	delete projectile;
}

void Combat::update()
{
	restCooldown -= Time::deltaTime;

	if (restCooldown < 0)
	{
		restCooldown = 0;
	}
}

bool Combat::attack(glm::vec2 direction)
{
	if (restCooldown != 0)
	{
		return false;
	}
		
	if (melee)
	{

	}
	else
	{
		
	}

	restCooldown = calcCooldown();
	return true;
}

float Combat::calcCooldown()
{
	return 1.0f / attackSpeed;
}