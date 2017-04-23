#include <Trappist-1\entities\Player.hpp>
#include <Trappist-1\abilities\AbilityManager.hpp>

Player::Player(AbilityManager *manager) : Entity()
{
	abilityManager = manager;
}

Player::~Player()
{
	delete abilityManager;
}

void Player::update()
{
	Entity::update();
	abilityManager->update();
}