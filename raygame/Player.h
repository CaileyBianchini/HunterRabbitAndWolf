#pragma once
#include "Agent.h"

class Player : public Agent
{
public:
	Player() : Agent() {}
	Player(float x, float y, float collisionRadius, const char* spriteFilePath, float maxSpeed, float maxForce = 1);
	void update(float deltatime) override;
	void debug() override;
};

