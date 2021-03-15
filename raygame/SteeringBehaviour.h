#pragma once
#include "Behaviour.h"
#include <Vector2.h>

class SteeringBehaviour : public Behaviour
{
public:
	virtual MathLibrary::Vector2 calculateForce(Agent* owner) = 0;
	virtual float getForceScale() { return m_forceScale; }
	virtual void setForceScale(float forceScale) { m_forceScale = forceScale; }

private:
	float m_forceScale = 1;
};
