#pragma once

#include <glm\vec2.hpp>

enum ComponentType
{
	ANIMATOR,
	COLLIDER,
	HEALTH,
	MOVEMENT,
	COMBAT,
	COMPONENTCOUNT
};

class Entity;
class Collider;

class Component
{
public:
	Component(Entity *entity) : entity(entity){}
	virtual ~Component(){}

	// Updates the Component.
	virtual void update(){}

	// Gets called after the entities moved.
	virtual void onMove(const glm::vec2 &movement) { }

	// Gets called when the entities tries to move. The bool returned can deny this if returning false.
	virtual bool canMove(const glm::vec2 &movement) { return true; }

	// Gets called when the entities collides with another collider and returns whether it can pass. May be called twice per collision! :(
	virtual bool onCollision(Collider *other) { return false; }

	ComponentType type;

protected:
	Entity *entity;
};