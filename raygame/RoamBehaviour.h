#pragma once
#include "SteeringBehaviour.h"
#include "Behaviour.h"

class Actor;

class RoamBehaviour :
	public SteeringBehaviour
{
public:
	RoamBehaviour();
	RoamBehaviour(Actor* target, float seekForce = 1);

	Actor* getTarget() { return m_target; }
	void setTarget(Actor* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;

private:
	Actor* m_target;
	float m_seekForce;
	float circleDistance = 5;
	float circleRadius = 5;
	float wanderAngle = 20;
};

