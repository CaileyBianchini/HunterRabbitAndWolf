#pragma once
#include "Behaviour.h"
class RoamBehaviour :
	public Behaviour
{
public:
	/*MathLibrary::Vector2 wander();*/

private:
	Agent* m_target;
};

