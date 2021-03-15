#include "ABDecision.h"


ABDecision::ABDecision(Decision* leftChild, Decision* rightChild)
{
	m_leftChild = leftChild;
	m_rightChild = rightChild;
}

void ABDecision::makeDecision(Agent* agent, float deltaTime)
{
	//call the checkcondition function for the decision 
	if (checkCondition(agent, deltaTime))
	{
		//if the function returns true and the left child isn't null,
		//move to the left node
		if (m_leftChild)
			m_leftChild->makeDecision(agent, deltaTime);
	}
	else
	{
		//if the function returns true and the right child isn't null,
		//move to the right node
		if (m_rightChild)
			m_rightChild->makeDecision(agent, deltaTime);
	}
}
