#include "Edge.h"
#include <raylib.h>
#include "Node.h"

Edge::Edge(Node* node1, Node* node2) : Actor(0, 0, 0, ' ', 0)
{
	connectedNode1 = node1;
	connectedNode2 = node2;
}

void Edge::draw()
{
	DrawLine(getWorldPosition().x * 32, getWorldPosition().y * 32,
		connectedNode2->getWorldPosition().x * 32, connectedNode2->getWorldPosition().y * 32, WHITE);
}

void Edge::update(float deltaTime)
{
	Actor::update(deltaTime);
	//up[dates the position to match the position of the first connected node
	setWorldPostion(connectedNode1->getWorldPosition());
}
