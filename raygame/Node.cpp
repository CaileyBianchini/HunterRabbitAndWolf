#include "Node.h"
#include "Edge.h"
#include <raylib.h>

Node::Node(int x, int y, int nodeSize)
{
	graphPosition.x = x;
	graphPosition.y = y;
	size = nodeSize;
}

void Node::draw()
{
	//draw a circle that represents the node
	DrawCircle(getWorldPosition().x * 32, getWorldPosition().y * 32, size, GetColor(color));

	//draw all edges connected to this node
	for (int i = 0; i < edges.size(); i++)
	{
		//checks if the node is the first connected node to prevent the edge from drawing twice
		if (edges[i]->connectedNode1->graphPosition == graphPosition)
			edges[i]->draw();
	}
}

void Node::update(float deltaTime)
{
	Actor::update(deltaTime);

	for (int i = 0; i < edges.size(); i++)
		if (edges[i]->connectedNode1->graphPosition == graphPosition)
			edges[i]->update(deltaTime);
}
