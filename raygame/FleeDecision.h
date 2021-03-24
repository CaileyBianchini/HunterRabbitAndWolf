#pragma once
#include "ABDecision.h"
class FleeDecision :
	public ABDecision
{
public:
	using ABDecision::ABDecision;

	void makeDecision(Agent* agent, float deltaTime) override;
};
