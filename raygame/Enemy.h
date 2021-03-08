#pragma once
#include "Character.h"
class Enemy :
	public Character
{
public:
    /// <param name="x">Position on the x axis</param>
    /// <param name="y">Position on the y axis</param>
    /// <param name="icon">The symbol that will appear when drawn</param>
    /// <param name="maxForce">The largest of the magnigtude of the force vector can be</param>
    Enemy(float x, float y, float collisionRadius, const char* spriteFilePath, 
        Actor* target, float health = 1, float damage = 1, float maxSpeed = 1, float maxForce = 1);
    void update(float deltaTime) override;
    virtual Actor* getTarget() { return m_target; }
    virtual void setTarget(Character* agent) { m_target = agent; }

private:
    Actor* m_target;
};

