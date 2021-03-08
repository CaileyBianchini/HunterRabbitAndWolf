#pragma once

class Agent;

class Behaviour
{
public:
	virtual void update(Agent* owner, float deltaTime) = 0;
	virtual void draw() {};

	virtual float getForceScale() { return m_forceScale; }
	virtual float setForceScale(float forceScale) { m_forceScale = forceScale; }

private:
	float m_forceScale = 1;
};