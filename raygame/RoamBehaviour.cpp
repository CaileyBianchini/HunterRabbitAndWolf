#include "RoamBehaviour.h"
#include "Agent.h"
#include "Actor.h"
#include "SteeringBehaviour.h"

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
	MathLibrary::Vector2 desiredVelocity = direction + (agent->getForward() * .5);
	//
	MathLibrary::Vector2 steeringForce = desiredVelocity / .25;

	return steeringForce;
}

void RoamBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
