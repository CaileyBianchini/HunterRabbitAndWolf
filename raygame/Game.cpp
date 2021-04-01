#include "Game.h"
#include "raylib.h"
#include "Player.h"
#include "Agent.h"
#include "SeekBehaviour.h"
#include "FleeBehaviour.h"
#include "PursueBehaviour.h"
#include "RoamBehaviour.h"
#include "DecisionBehaviour.h"
#include "PursueDecision.h"
#include "FleeDecision.h"
#include "ComplexEnemy.h"
#include "Graph.h"
#include "Enemy.h"

bool Game::m_gameOver = false;
Scene** Game::m_scenes = new Scene*;
int Game::m_sceneCount = 0;
int Game::m_currentSceneIndex = 0;
int Game::m_screenWidth = 1024;
int Game::m_screenHeight = 760;
int change = 0;


Game::Game()
{
	m_gameOver = false;
	m_scenes = new Scene*;
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
	m_instance = this;
}

void Game::start()
{
	m_screenWidth = 1024;
	m_screenHeight = 760;

	InitWindow(m_screenWidth, m_screenHeight, "raylib [core] example - basic window");
	m_camera->offset = { (float)m_screenWidth / 2, (float)m_screenHeight / 2 };
	m_camera->target = { (float)m_screenWidth / 2, (float)m_screenHeight / 2 };
	m_camera->zoom = 1;

	//initialize agents
	Player* player = new Player(10, 10, 3, "Images/hunter.png", 5, 5);

	Agent* bunnyName = new Agent(15, 15, 1, "bunny", 5, 5);
	Agent* bunny = new Agent(15, 15, 1, "Images/player.png", 5, 5);
	bunny->addChild(bunnyName);

	Agent* wolfName = new Agent(20, 20, 1, "wolf", 5, 5);
	Agent* wolf = new Agent(20, 20, 1, "Images/enemy.png", 5, 5);
	wolf->addChild(wolfName);
	

	/*decisions*/
	/*PursueDecision* pursueDecision = new PursueDecision();
	FleeDecision* fleeDecision = new FleeDecision();
	DecisionBehaviour* pursueBehaviour = new DecisionBehaviour(pursueDecision);
	DecisionBehaviour* fleeBehaviour = new DecisionBehaviour(fleeDecision);*/

	//create a new steering behaviour
	PursueBehaviour* pursue = new PursueBehaviour(player);
	wolf->addBehaviour(pursue);
	FleeBehaviour* flee = new FleeBehaviour(player);
	bunny->addBehaviour(flee);

	//path finding

	Graph* graph = new Graph(10, 10, 10, 1);

	graph->setWorldPostion({ 2, 2 });
	graph->BFS(0, 0, 9, 0);

	//initalize the scene
	Scene* scene = new Scene();
	scene->addActor(player);
	scene->addActor(bunny);
	scene->addActor(wolf);
	addScene(scene);
	SetTargetFPS(60);
}

void Game::update(float deltaTime)
{
	getCurrentScene()->update(deltaTime);
	change++;
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(BLUE);

	getCurrentScene()->draw();

	EndMode2D();
	EndDrawing();
}

void Game::end()
{
	CloseWindow();
}

MathLibrary::Matrix3* Game::getWorld()
{
	return getCurrentScene()->getWorld();
}

void Game::run()
{
	start();

	while (!m_gameOver && !RAYLIB_H::WindowShouldClose())
	{
		float deltaTime = RAYLIB_H::GetFrameTime();
		update(deltaTime);
		draw();
	}

	end();
}

Scene* Game::getScene(int index)
{
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Game::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Game::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Game::addScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return -1;

	//Create a new temporary array that one size larger than the original
	Scene** tempArray = new Scene*[m_sceneCount + 1];

	//Copy values from old array into new array
	for (int i = 0; i < m_sceneCount; i++)
	{
		tempArray[i] = m_scenes[i];
	}

	//Store the current index
	int index = m_sceneCount;

	//Sets the scene at the new index to be the scene passed in
	tempArray[index] = scene;

	//Set the old array to the tmeporary array
	m_scenes = tempArray;
	m_sceneCount++;

	return index;
}

bool Game::removeScene(Scene* scene)
{
	//If the scene is null then return before running any other logic
	if (!scene)
		return false;

	bool sceneRemoved = false;

	//Create a new temporary array that is one less than our original array
	Scene** tempArray = new Scene*[m_sceneCount - 1];

	//Copy all scenes except the scene we don't want into the new array
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
		{
			sceneRemoved = true;
		}
	}

	//If the scene was successfully removed set the old array to be the new array
	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}
		

	return sceneRemoved;
}

void Game::setCurrentScene(int index)
{
	//If the index is not within the range of the the array return
	if (index < 0 || index >= m_sceneCount)
		return;

	//Call end for the previous scene before changing to the new one
	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	//Update the current scene index
	m_currentSceneIndex = index;
}

bool Game::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Game::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Game::destroy(Actor* actor)
{
	getCurrentScene()->removeActor(actor);
	if (actor->getParent())
		actor->getParent()->removeChild(actor);
	actor->end();
	delete actor;
}

void Game::setGameOver(bool value)
{
	Game::m_gameOver = value;
}

Game::Maze::Maze(TileKey map[Maze::HEIGHT][Maze::WIDTH])
{
	//Generate the map
	generate(map);
}

Game::Maze::~Maze()
{
	for (int y = 0; y < m_size.y; y++) {
		for (int x = 0; x < m_size.x; x++) {
			delete m_grid[x][y].actor;
			delete m_grid[x][y].node;
		}
	}
}

//Tile Game::Maze::getTile(MathLibrary::Vector2 position)
//{
//	int x = (int)(position.x / TILE_SIZE);
//	int y = (int)(position.y / TILE_SIZE);
//	if (x >= 0 && x < Maze::WIDTH && y >= 0 && y < Maze::HEIGHT)
//		return m_grid[x][y];
//	else
//		return m_grid[0][0];
//}
//
//MathLibrary::Vector2 Game::Maze::getPosition(Tile tile)
//{
//	return MathLibrary::Vector2{ tile.x * TILE_SIZE + (TILE_SIZE / 2.0f), tile.y * TILE_SIZE + (TILE_SIZE / 2.0f) };
//}
//
//Tile Game::Maze::createTile(int x, int y, TileKey key)
//{
//	// Create a new tile at the given location
//	Tile tile{ x, y };
//	MathLibrary::Vector2 position = getPosition(tile);
//	// Set the cost and actor of each tile
//	switch (key) {
//	case TileKey::OPEN:
//		tile.cost = 1.0f;
//		break;
//	case TileKey::WALL:
//		tile.cost = 100.0f;
//		tile.actor = new Wall(position.x, position.y);
//		addActor(tile.actor);
//		break;
//	}
//	return tile;
//}
//
//void Game::Maze::generate(TileKey map[Maze::HEIGHT][Maze::WIDTH])
//{
//	for (int y = 0; y < m_size.y; y++) {
//		for (int x = 0; x < m_size.x; x++) {
//			// Create the tile
//			Tile currentTile = createTile(x, y, map[y][x]);
//			// Add node to graph
//			currentTile.node = new Graph::Node();
//			currentTile.node->position = getPosition(currentTile);
//			if (x > 0) { // west connection
//				Tile other = m_grid[x - 1][y];
//				currentTile.node->connections.push_back(Graph::Edge{ other.node, other.cost });
//				other.node->connections.push_back(Graph::Edge{ currentTile.node, currentTile.cost });
//			}
//			if (y > 0) { // north connection
//				Tile other = m_grid[x][y - 1];
//				currentTile.node->connections.push_back(Graph::Edge{ other.node, other.cost });
//				other.node->connections.push_back(Graph::Edge{ currentTile.node, currentTile.cost });
//			}
//			// Set the tile on the grid
//			m_grid[x][y] = currentTile;
//		}
//	}
//}
