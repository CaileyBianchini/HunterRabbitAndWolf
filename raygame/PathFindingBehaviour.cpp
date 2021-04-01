#include "PathFindingBehaviour.h"
#include "Game.h"

void PathfindBehavior::update(Agent* owner, float deltaTime)
{
	////Don't update if disabled or no target
	//if (!getEnabled() || !m_target)
	//	return;

	////Find the positions and tiles of the owner and target
	//MathLibrary::Vector2 ownerPosition = owner->getWorldPosition();
	//MathLibrary::Vector2 destinationPosition = findDestination(owner);
	//Game::Tile ownerTile = m_maze->getTile(ownerPosition);
	//Game::Tile destinationTile = m_maze->getTile(destinationPosition);

	////Update the path if needed
	//if (m_needPath)
	//	updatePath(owner, destinationPosition);

	////Find the position and tile of the next node
	//MathLibrary::Vector2 nextPosition = ownerPosition;
	//if (!m_path.empty())
	//	nextPosition = m_path.front()->position;
	//Maze::Tile nextTile = m_maze->getTile(nextPosition);

	////If owner is at the front node, go to the following node
	//if (ownerTile.x == nextTile.x && ownerTile.y == nextTile.y) {
	//	if (!m_path.empty())
	//		m_path.pop_front();
	//	m_needPath = true;
	//}

	////Find the direction
	//MathLibrary::Vector2 direction = { 0.0f, 0.0f };
	//if (!m_path.empty())
	//	direction = MathLibrary::Vector2::normalize(m_path.front()->position - ownerPosition);

	////Calculate the force
	//MathLibrary::Vector2 desiredVelocity = direction * owner->getMaxSpeed();
	//MathLibrary::Vector2 steeringForce = desiredVelocity - owner->getVelocity();

	////Apply the force
	//owner->applyForce(steeringForce);
}

void PathfindBehavior::draw(Agent* owner)
{
	/*for (NodeGraph::Node* node : m_path)
	{
		NodeGraph::drawNode(node, m_color);
	}*/
}

void PathfindBehavior::updatePath(Agent* owner)
{
	updatePath(owner, m_target->getWorldPosition());
}

void PathfindBehavior::updatePath(Agent* owner, MathLibrary::Vector2 destination)
{
	/*NodeGraph::Node* ownerNode = m_maze->getTile(owner->getWorldPosition()).node;
	NodeGraph::Node* targetNode = m_maze->getTile(destination).node;
	m_path = NodeGraph::findPath(ownerNode, targetNode);
	if (!m_path.empty()) m_path.pop_front();
	m_needPath = false;*/
}