#include "SimpleEnemy.h"
#include "SeekBehaviour.h"

bool SimpleEnemy::checkTargetInSight()
{
	//Check if target is null. If so return false

	//Find the direction vector that represents where the target is relative to the enemy

	//Find the dot product of the enemy's forward and the direction vector

	//Find the angle using the dot product

	//Check if that angle is greater than the enemy's viewing angle(any value you see fit is fine)

	//Return if the enemy saw the target
	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{
	//Check to see if the enemy ran into the player

	//If the enemy has run into the player, deal damage to the player

	//If the player's health is less than 0, set the target to be nullptr
}

void SimpleEnemy::start()
{
	//Call base start function
	Enemy::start();

	//Set the default state of the enemy
	m_currentState = WANDER;

	//Initialize member variables
	m_seek = getBehaviour<SeekBehaviour>();
	//m_wander = getBehaviour<WanderBehaviour>();

	//Set the target to be the base class target
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	//Create a switch statement for the state machine.
	//The switch should transition to the wander state if the target is not in sight.
	//You can set the wander force to be whatever value you see fit but be sure to 
	//set the seek force to be 0.

	//The switch should transition to the seek state if the target is in sight.
	//You can set the seek force to be whatever value you see fit, but be sure to
	//set the wander force to be 0.

	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}

