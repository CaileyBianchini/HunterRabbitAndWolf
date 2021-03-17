#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <raylib.h>
#include <deque>

Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_width = width;
	m_height = height;

	createGraph(nodeSize, nodeSpacing);
}

void Graph::draw()
{
	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->draw();
}

void Graph::update(float deltaTime)
{
	Actor::update(deltaTime);

	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->update(deltaTime);
}

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	if (!start || !goal)
		return;

	start->color = ColorToInt(GREEN);
	start->visited = true;

	Node* currentNode = start;

	std::deque<Node*> queue;
	queue.push_front(start);

	while (!queue.empty())
	{
		currentNode = queue[0];
		queue.pop_front();

		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node* currentEdgeEnd = nullptr;

			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1);
				
			else
				currentEdgeEnd = currentEdgeEnd->edges[i]->connectedNode2;
			
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_front(currentEdgeEnd);
			}
			
		}
	}
}

Node* Graph::getNode(int xPos, int yPos)
{
	if(xPos < 0 || xPos > m_width || yPos < 0 || yPos > m_height)
		return nullptr;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
			return m_nodes[i];
	}
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;

	//loops for the amount of nodes in the graph
	for (int i = 0; i < m_width * m_height; i++)
	{
		Node* currentNode = new Node(xPos, yPos, nodeSize);

		//set the local offset for the current position and size
		MathLibrary::Vector2 nodeLocalPosition = { xPos * nodeSpacing, yPos * nodeSpacing };
		currentNode->setLocalPosition(nodeLocalPosition);

		//add the node as a child of the grid and update the list
		addChild(currentNode);
		m_nodes.push_back(currentNode);

		for (int j = 0; j < m_nodes.size(); j++)
		{
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;

			if (displacement.getMagnitude() <= 1.42 && displacement.getMagnitude() > 0)
			{
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}

		xPos++;

		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}
