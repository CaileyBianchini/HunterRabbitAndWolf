#include "FleeDecision.h"
#include "ComplexEnemy.h"
#include "PursueBehaviour.h"
#include "RoamBehaviour.h"
#include "EvadeBehaviour.h"

void FleeDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		//this lets the behaviour of the enemy know that "oh hey your supposed wandering but if you see the enemy you flee"
		enemy->getPursue()->setEnabled(false);
		enemy->getRoam()->setEnabled(true);
		enemy->getEvade()->setEnabled(false);
		if (enemy->checkTargetInRange(3))
		{
			enemy->getPursue()->setEnabled(false);
			enemy->getRoam()->setEnabled(false);
			enemy->getEvade()->setEnabled(true);
		}
	}
}