#include "DecisionBehaviour.h"
#include "Decision.h"
void DecisionBehaviour::update(Agent* agent, float deltaTime)
{
	if (agent)
		m_root->makeDecision(agent, deltaTime);
}
