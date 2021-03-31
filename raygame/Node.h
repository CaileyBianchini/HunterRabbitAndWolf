#pragma once
#include "Actor.h"
#include <vector>
#include <deque>
#include <Vector2.h>

class Edge;

class Node :
	public Actor
{
public:
	Node(int x, int y, int nodeSize);
	std::vector<Edge*> edges;
	MathLibrary::Vector2 graphPosition;
	int color = 0xFFFFFFFF;
	int size = 1;
	bool visited;
	void draw() override;
	void update(float deltaTime) override;

	void begin();

	MathLibrary::Vector2 position;
	std::vector<Edge> connections;
	float gScore;

	Node* previous;
};

