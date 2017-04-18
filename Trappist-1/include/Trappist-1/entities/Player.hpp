#pragma once

#include <Trappist-1\entities\Entity.hpp>

class AbilityManager;

class Player : public Entity
{
public:
	Player(AbilityManager *manager);
	~Player();

	void update();

	AbilityManager *abilityManager;

private:

};