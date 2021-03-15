#include "PursueBehaviour.h"
#include "Agent.h"
#include "Actor.h"

PursueBehaviour::PursueBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

PursueBehaviour::PursueBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(1);
}

MathLibrary::Vector2 PursueBehaviour::calculateForce(Agent* agent)
{
	//Pursue is just seek but you add the target's velocity to the position that's being seeked

	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize((m_target->getWorldPosition() + m_target->getVelocity()) - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//subtract current velocity from desired velocity to find sterring force
	MathLibrary::Vector2 steeringForce = desiredVelocity - agent->getVelocity();

	return steeringForce;
}

void PursueBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}