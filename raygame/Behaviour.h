#pragma once

class Agent;

class Behaviour
{
public:
	virtual void update(Agent* owner, float deltaTime) = 0;
};