#include "ComplexEnemy.h"
#include "EvadeBehaviour.h"
#include "RoamBehaviour.h"
#include "PursueBehaviour.h"
#include "Player.h"

void ComplexEnemy::start()
{
	Enemy::start();

	//initalize behaviours
	m_roamBehaviour = getBehaviour<RoamBehaviour>();
	m_pursueBehaviour = getBehaviour<PursueBehaviour>();
	m_evadeBehaviour = getBehaviour<EvadeBehaviour>();

	//set target to target given from the base class
	setTarget(Enemy::getTarget());
}

void ComplexEnemy::setTarget(Actor* target)
{
	Enemy::setTarget(target);
	m_pursueBehaviour->setTarget(target);
	m_evadeBehaviour->setTarget(target);
}

void ComplexEnemy::onCollision(Actor* other)
{
	Enemy::onCollision(other);

	Player* player = dynamic_cast<Player*>(other);

	//if the actor is a player, damage it
	if (player)
	{
		player->takeDamage(getDamage());

		//if the player has died, set the target to the null
		if (player->getHealth() <= 0)
			setTarget(nullptr);
	}
}

void ComplexEnemy::update(float deltaTime)
{

}

bool ComplexEnemy::checkTargetInSight(float angle)
{
	return false;
}

bool ComplexEnemy::checkTargetInRange(float range)
{
	return false;
}
