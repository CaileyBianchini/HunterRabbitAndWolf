#pragma once
#include "Enemy.h"

class RoamBehaviour;
class PursueBehaviour;
class EvadeBehaviour;

class ComplexEnemy :
	public Enemy
{
public:
	using Enemy::Enemy;
	void start() override;

	void setTarget(Actor* target) override;

	void onCollision(Actor* other) override;

	RoamBehaviour* getRoam() { return m_roamBehaviour; }
	PursueBehaviour* getPursue() { return m_pursueBehaviour; }
	EvadeBehaviour* getEvade() { return m_evadeBehaviour; }

	void update(float deltaTime) override;

	bool checkTargetInSight(float angle = 2);

	bool checkTargetInRange(float range);

private:
	RoamBehaviour* m_roamBehaviour;
	PursueBehaviour* m_pursueBehaviour;
	EvadeBehaviour* m_evadeBehaviour;
};

