#pragma once

#include <Trappist-1\abilities\Ability.h>

class Entity;

class AbilityManager
{
public:
	AbilityManager();
	~AbilityManager();

	// Updates all the abilities and casts them if their key is pressed.
	void update();

	// Sets the ability of slot index to the given type.
	void setAbility(int index, AbilityType type);

	// Sets entity! -Captain Obvious
	void setEntity(Entity *entity);

	// Casts the ability int the given slot.
	bool cast(int index);

	int getSize() const;

private:
	Ability* getAbility(AbilityType type);

	Entity *entity;
	Ability *abilities[5];
	int size;
};

inline int AbilityManager::getSize() const
{
	return size;
}

inline void AbilityManager::setEntity(Entity *entity)
{
	this->entity = entity;
}

