#pragma once
#include "Actor.h"

class Node;

class Edge :
	public Actor
{
public:
	Edge(Node* node1, Node* node2);
	Node* connectedNode1;
	Node* connectedNode2;
	float cost;
	void draw() override;
	void update(float deltaTime) override;
};

