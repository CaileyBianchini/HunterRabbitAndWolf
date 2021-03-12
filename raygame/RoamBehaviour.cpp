#include "RoamBehaviour.h"
#include "Agent.h"
#include "Actor.h"
#include "SteeringBehaviour.h"

RoamBehaviour::RoamBehaviour()
{
	m_target = nullptr;
	setForceScale(1);
}

RoamBehaviour::RoamBehaviour(Actor* target, float seekForce)
{
	m_target = target;
	setForceScale(1);
}

MathLibrary::Vector2 RoamBehaviour::calculateForce(Agent* agent)
{
	//circle center
	MathLibrary::Vector2 centerCircle = agent->getForward() * circleDistance;
	//create a vector for the center of the circle while calculating the position of the arrow by adding the offset to it
	MathLibrary::Vector2 circle = centerCircle * getForceScale();
	//randomizes the wanderAngle
	wanderAngle += (rand() * wanderAngle) - (wanderAngle * .5);
	//This will create a random vector for direction
	MathLibrary::Vector2 direction = MathLibrary::Vector2(cos(wanderAngle), sin(wanderAngle)).getNormalized();
	//Scale the direction vector by circleRadious
	MathLibrary::Vector2 desiredVelocity = (direction * circleRadius) + centerCircle;
	//subtract current velocity from desired velocity to find sterring force
	MathLibrary::Vector2 steeringForce = desiredVelocity + circle;
	steeringForce = steeringForce.getNormalized();
	return steeringForce;
}

void RoamBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		agent->addForce(calculateForce(agent));
}
