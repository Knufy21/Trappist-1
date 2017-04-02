#pragma once

#include <vector>

class Collider;

namespace CollisionDetector
{
	// Returns a vector containing all colliders the collider collided with #tonguetwister
	void checkCollisions(Collider *collider, std::vector<Collider*> &v);

	// Returns whether the two colliders collide
	bool doCollide(Collider *collider1, Collider *collider2);
}
