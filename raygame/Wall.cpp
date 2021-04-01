#include "Wall.h"
#include "Game.h"

Wall::Wall(float x, float y)
	: Actor(x, y, Game::TILE_SIZE / 2.0f, 0, 0x3333CCFF)
{
	setStatic(true);
}