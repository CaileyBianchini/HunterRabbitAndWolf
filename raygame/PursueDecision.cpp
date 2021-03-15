#include "PursueDecision.h"
#include "ComplexEnemy.h"
#include "PursueBehaviour.h"
#include "RoamBehaviour.h"
#include "EvadeBehaviour.h"

void PursueDecision::makeDecision(Agent* agent, float deltaTime)
{
	ComplexEnemy* enemy = dynamic_cast<ComplexEnemy*>(agent);

	if (enemy)
	{
		enemy->getPursue()->setEnabled(true);
		enemy->getRoam()->setEnabled(false);
		enemy->getEvade()->setEnabled(false);
	}
}
