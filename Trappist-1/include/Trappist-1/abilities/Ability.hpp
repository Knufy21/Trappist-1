#pragma once

#include <functional>

enum AbilityType
{
	DASH,
	ABILITYCOUNT
};

class Entity;

class Ability
{
public:
	Ability(AbilityType type, float cooldown, std::function<bool(Entity *entity)> castFunction);

	// Updates the cooldown.
	void update();

	// Casts the ability and returns whether it was successful.
	bool cast(Entity *entity);

	float getCooldown() const;

	float getRestCooldown() const;

private:
	std::function<bool(Entity *entity)> castFunction;

	AbilityType type;
	float cooldown;
	float restCooldown;
};

inline float Ability::getCooldown() const
{
	return cooldown;
}

inline float Ability::getRestCooldown() const
{
	return restCooldown;
}

