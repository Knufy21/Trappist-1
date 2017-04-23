#pragma once

#include <Trappist-1\components\Component.hpp>

class Combat : public Component
{
public:
	Combat(Entity *entity, float attackSpeed, float damage);
	Combat(Entity *entity, float attackSpeed, float damage, Entity *projectile);
	~Combat();

	void update() override;

	// Requests an attack. Returns if it was successful.
	bool attack(glm::vec2 direction);

	// Sets the attackspeed (hits per second).
	void setAttackSpeed(float attackSpeed);

	// Returns the attackspeed (hits per second).
	float getAttackSpeed() const;

	// Sets the damage of the attacks/the projectile.
	void setDamage(float damage);

	// Returns the damage of the attacks/the projectile.
	float getDamage() const;

private:
	// Returns the cooldown for the attacks.
	float calcCooldown();

	float damage;
	float attackSpeed;
	float restCooldown;
	bool melee;
	Entity *projectile;
};

inline void Combat::setAttackSpeed(float attckSpeed)
{
	this->attackSpeed = attackSpeed;
}

inline float Combat::getAttackSpeed() const
{
	return attackSpeed;
}

inline void Combat::setDamage(float damage)
{
	this->damage = damage;
}

inline float Combat::getDamage() const
{
	return damage;
}