#pragma once
#include "Behaviour.h"
#include <Vector2.h>

class SteeringBehaviour : public Behaviour
{
public:
	virtual MathLibrary::Vector2 calculateForce(Agent* owner) = 0;
};
