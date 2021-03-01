#pragma once
#include "SteeringBehaviour.h"

class SeekBehaviour :
	public SteeringBehaviour
{
public:
	SeekBehaviour() { m_target = nullptr; }
	SeekBehaviour(Agent* target) { m_target = target; }

	Agent* getTarget() { return m_target; }
	void setTarget(Agent* target) { m_target = target; }

	MathLibrary::Vector2 calculateForce(Agent* agent) override;
	void update(Agent* agent, float deltaTime) override;
private:
	//the agent the behaviour is seeking
	Agent* m_target;
};

