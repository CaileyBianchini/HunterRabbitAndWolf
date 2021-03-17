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
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
				
			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;
			
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_front(currentEdgeEnd);
			}
			
		}
	}
}

void Graph::Djikstra(int startX, int startY, int goalX, int goalY)
{
	//Create a node pointer that points to the start node
	Node* start = getNode(startX, startY);
	//Create a node pointer that points to the goal node
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	if (!start || !goal)
		return;

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);
	start->visited = true;

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode = start;
	//Create an open list
	std::deque<Node*> open;
	//Create a closed list
	std::deque<Node*> closed;
	//Add start to the open list
	open.push_front(start);

	//Loop while the open list is not empty

		//Sort the items in the open list by the g score

		//Set the iterator to be the first item in the open list

		//Check if the iterator is pointing to the goal node

			//Mark the goal as being found by changing its color
				//Return the new path found

		//end if statement

		//Pop the first item off the open list
		//Add the first item to the closed list

		//Loop through all of the edges for the iterator

			//Create a node pointer to store the other end of the edge

			//Check if the iterator is on the second end of the node
				//Set the edge end pointer to be the first end of the node
			//Otherwise if the iterator is on the first end of the node...
				//set the edge end pointer to be the second end of the node
			// end if statement

			//Check if node at the end of the edge is in the closed list

				//Create an int and set it to be the g score of the iterator plus the cost of the edge


				//Check if the node at the end ofthe edge is in the open list

					//Mark the node as visited by changing its color
					//Set the nodes g score to be the g score calculated earlier
					//Set the nodes previous to be the iterator
					//Add the node to the open list

				//Otherwise if the g score is less than the node at the end of the edge's g score...

					//Mark the node as visited by changing its color
					//Set its g score to be the g score calculated earlier
					//Set its previous to be the current node

				//end if statement
		//end loop
	//end loop
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
