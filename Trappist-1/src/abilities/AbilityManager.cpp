#include <Trappist-1\abilities\AbilityManager.h>
#include <Trappist-1\entities\Entity.hpp>

AbilityManager::AbilityManager()
{
	size = 5;
}

AbilityManager::~AbilityManager()
{
	for (size_t i = 0; i < size; i++)
	{
		delete abilities[i];
	}
}

void AbilityManager::update()
{
	for (size_t i = 0; i < size; i++)
	{
		if (abilities[i] != nullptr)
		{
			abilities[i]->update();
		}
	}
}

bool AbilityManager::cast(int index)
{
	if (index < size)
	{
		if (abilities[index] != nullptr)
		{
			return abilities[index]->cast(entity);
		}
	}
	return false;
}

void AbilityManager::setAbility(int index, AbilityType type)
{
	if (index < size)
	{
		delete abilities[index];
		abilities[index] = getAbility(type);
	}
}

Ability* AbilityManager::getAbility(AbilityType type)
{
	switch (type)
	{
	case AbilityType::DASH:
		return new Ability(AbilityType::DASH, 1, [](Entity *entity) { entity->move(entity->getLookDirection() * 1000.0f); return true; });
	default:
		return new Ability(AbilityType::ABILITYCOUNT, 0, [](Entity *entity) { return false; });
		break;
	}
}