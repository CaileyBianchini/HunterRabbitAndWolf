#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <raylib.h>
#include <deque>
#include <vector>
#include <Vector2.h>


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

	//this will give the color for those visited
	start->color = ColorToInt(GREEN);
	start->visited = true;

	//initializes the iterrators
	Node* currentNode = start;
	//turns its into a a queue variable
	std::deque<Node*> queue;
	queue.push_front(start);

	//this will search for the goal while the queue isn't empty
	while (!queue.empty())
	{
		//Set the current Node to be the first item in the queue and remove the previous first item
		currentNode = queue[0];
		queue.pop_front();

		//this will return the color as yellow because the current node its at is equal to the goal
		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return;
		}
		//If the Node wasn't the goal, loop through its edges
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a pointer to the end of the current Edge
			Node* currentEdgeEnd = nullptr;

			//Set the pointer to the opposite end of the Edge
			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
				
			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			//If the Node at the end ofthe Edge hasn't been visited, mark as visited and add to the queue
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_front(currentEdgeEnd);
			}
			
		}
	}
}

//this just grabs all the nodes
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

Node* Graph::findPath(Node* start, Node* end)
{
	//This helps use start and end without errors
	Node* starter = start;
	Node* goal = end;

	std::deque<Node*> queue;

	if (!starter || !goal)
		return /*queue*/;

	starter->color = ColorToInt(GREEN);
	starter->visited = true;

	Node* currentNode = starter;

	queue.push_front(starter);

	while (!queue.empty())
	{
		currentNode = queue[0];
		queue.pop_front();

		if (currentNode == goal)
		{
			currentNode->color = ColorToInt(YELLOW);
			return /*queue*/;
		}

		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			Node* currentEdgeEnd = nullptr;

			if (currentNode == currentNode->edges[i]->connectedNode2)
			{
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			}

			else
			{
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;
			}

			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_front(currentEdgeEnd);
			}

		}
	}
}

void Graph::drawGraph(Node* start)
{
	Node* drawnList;
	drawConnectedNodes(start, drawnList);
	delete drawnList;
}

void Graph::drawNode(Node* node, int color)
{
	static char buffer[10];
	sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle((int)node->position.x, (int)node->position.y, 16, GetColor(color));
	//Draw the inner circle
	DrawCircle((int)node->position.x, (int)node->position.y, 14, BLACK);
	//Draw the text
	DrawText(buffer, (int)node->position.x, (int)node->position.y, 24, RAYWHITE);
}

void Graph::drawConnectedNodes(Node* node, Node* drawnList)
{
	drawNode(node);
	/*drawnList.push_back(node);*/

	//For each Edge in this node's connections
	for (Edge e : node->connections) {
		//Draw the Edge
		DrawLine((int)node->position.x, (int)node->position.y, (int)e.target->position.x, (int)e.target->position.y, WHITE);
		//Draw the cost
		MathLibrary::Vector2 costPos = { (node->position.x + e.target->position.x) / 2, (node->position.y + e.target->position.y) / 2 };
		static char buffer[10];
		sprintf_s(buffer, "%.0f", e.cost);
		DrawText(buffer, (int)costPos.x, (int)costPos.y, 16, RAYWHITE);
		//Draw the target node
		if (std::find(drawnList->begin(), drawnList->end(), e.target) == drawnList->end()) {
			drawConnectedNodes(e.target, drawnList);
		}
	}
}