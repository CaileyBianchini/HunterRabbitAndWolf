#pragma once
class Agent;

///<sumary>
///Abstract class for all decisions
///<sumary>
class Decision
{
public:
	virtual void makeDecision(Agent* agent, float deltaTime) = 0;
};