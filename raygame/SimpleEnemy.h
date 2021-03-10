#pragma once
#include "Enemy.h"

enum EnemyState
{
	WANDER = 0,
	SEEK = 1
};

class RoamBehaviour;
class SeekBehaviour;

class SimpleEnemy :
	public Enemy
{

	using Enemy::Enemy;
	bool checkTargetInSight();

	void onCollision(Actor* other) override;
	void start() override;
	void update(float deltaTime) override;

	void setTarget(Actor* target) override;
private:
	EnemyState m_currentState;
	RoamBehaviour* m_wander;
	SeekBehaviour* m_seek;
};

