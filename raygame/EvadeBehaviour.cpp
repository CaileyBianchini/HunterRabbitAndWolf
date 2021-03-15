#include "EvadeBehaviour.h"
#include "Agent.h"
#include "Actor.h"

EvadeBehaviour::EvadeBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

EvadeBehaviour::EvadeBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(1);
}

MathLibrary::Vector2 EvadeBehaviour::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize((m_target->getWorldPosition() + m_target->getVelocity()) - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//adds current velocity from desired velocity to get away from sterring force
	MathLibrary::Vector2 steeringForce = desiredVelocity + agent->getVelocity();

	return steeringForce;
}

void EvadeBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}