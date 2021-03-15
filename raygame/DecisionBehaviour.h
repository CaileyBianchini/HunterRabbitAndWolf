#pragma once
#include "Behaviour.h"

class Decision;

class DecisionBehaviour :
	public Behaviour
{
public:
	DecisionBehaviour(Decision* root) { m_root = root; };
	void update(Agent* agent, float deltaTime) override;

private:
	Decision* m_root;
};

