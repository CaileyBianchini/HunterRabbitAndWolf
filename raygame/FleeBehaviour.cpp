#include "FleeBehaviour.h"
#include "Agent.h"
#include "Actor.h"

FleeBehaviour::FleeBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

FleeBehaviour::FleeBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(1);
}

MathLibrary::Vector2 FleeBehaviour::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * getForceScale();
	//adds current velocity from desired velocity to get away from sterring force
	MathLibrary::Vector2 steeringForce = desiredVelocity + agent->getVelocity();

	return steeringForce;
}

void FleeBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
