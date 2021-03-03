#include "RoamBehaviour.h"
#include "Agent.h"
#include "Actor.h"

RoamBehaviour::RoamBehaviour()
{
	m_target = nullptr;
	m_seekForce = 1;
}

RoamBehaviour::RoamBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	m_seekForce = seekForce;
}

MathLibrary::Vector2 RoamBehaviour::calculateForce(Agent* agent)
{
	//Find the direction to move in
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	//Scale the direction vector by the seekForce
	MathLibrary::Vector2 desiredVelocity = direction * m_seekForce;
	//adds current velocity from desired velocity to get away from sterring force
	MathLibrary::Vector2 steeringForce = desiredVelocity - direction;

	return steeringForce;
}

void RoamBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}