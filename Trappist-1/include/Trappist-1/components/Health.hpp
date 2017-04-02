#pragma once

#include <Trappist-1\components\Component.hpp>

class Health : public Component
{
public:
	Health(int maxHp, Entity *entity);

	// Returns the entitys HealthPoints.
	int getHp() const;

	// Damages the entity by dmg HealthPoints.
	void damage(int dmg);

private:
	int maxHp;
	int hp;

};

inline int Health::getHp() const
{
	return hp;
}
