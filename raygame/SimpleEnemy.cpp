#include "SimpleEnemy.h"

bool SimpleEnemy::checkTargetInSight()
{

	return false;
}

void SimpleEnemy::onCollision(Actor* other)
{

}

void SimpleEnemy::start()
{
	Enemy::start();

	m_currentState = WANDER;

	m_seek = getBehaviour<SeekBehaviour>();
	m_wander = getBehaviour<RoamBehaviour>();
	setTarget(Enemy::getTarget());
}

void SimpleEnemy::update(float deltaTime)
{
	//coments go here
	Enemy::update(deltaTime);
}

void SimpleEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_seek->setTarget(target);
}
