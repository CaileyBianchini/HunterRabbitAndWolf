#include "SeekBehaviour.h"
#include "Agent.h"

MathLibrary::Vector2 SeekBehaviour::calculateForce(Agent* agent)
{
	//do seek behaviout
	MathLibrary::Vector2 direction = MathLibrary::Vector2::normalize(m_target->getWorldPosition() - agent->getWorldPosition());
	return MathLibrary::Vector2();
}
