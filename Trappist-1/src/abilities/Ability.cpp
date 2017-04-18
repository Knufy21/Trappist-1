#include <Trappist-1\abilities\Ability.h>
#include <Trappist-1\util\Time.hpp>

Ability::Ability(AbilityType type, float cooldown, std::function<bool(Entity *entity)> castFunction)
{
	this->castFunction = castFunction;
	this->type = type;
	this->cooldown = cooldown;
	this->restCooldown = cooldown;
}

void Ability::update()
{
	restCooldown -= Time::deltaTime;
	if (restCooldown < 0)
	{
		restCooldown = 0;
	}
}

bool Ability::cast(Entity *entity)
{
	bool f = false;

	if (restCooldown == 0)
	{
		f = castFunction(entity);
		restCooldown = cooldown;
	}

	return f;
}