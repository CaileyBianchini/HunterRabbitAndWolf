#pragma once
#include "Scene.h"
#include "Graph.h"
#include "Node.h"
#include <Vector2.h>
class Camera2D;

static class Game : public Scene
{
public:
    

    struct Maze {
        /// <summary>
    /// A enumerator of tile types.
    /// MODIFY this list with any new tiles needed.
    /// The keys are not ordered.
    /// </summary>
        enum class TileKey {
            OPEN,
            WALL,
            MUD,
            GHOST
        };

        /// <summary>
        /// A single space in a Maze.
        /// </summary>
        struct Tile {
            int x;
            int y;
            float cost = 1.0f;
            Actor* actor = nullptr;
            Node* node = nullptr;
        };

        static const int WIDTH = 28;
        static const int HEIGHT = 31;
        static const int TILE_SIZE = 32;

    public:
        /// <param name="map">A 2D array of TileKeys arranged height by width</param>
        Maze(TileKey map[Maze::HEIGHT][Maze::WIDTH]);
        ~Maze();

        /// <summary>
        /// Get the size of the maze.
        /// </summary>
        /// <returns>a Vector2 storing the maze's width and height</returns>
        MathLibrary::Vector2 getSize() { return m_size; }

        /// <summary>
        /// Get the tile data at the given position.
        /// </summary>
        /// <param name="position">The position to check</param>
        /// <returns>A Tile with the data at the position</returns>
        Tile getTile(MathLibrary::Vector2 position);

        /// <summary>
        /// Get the position of the given tile.
        /// </summary>
        /// <param name="tile">The tile to check</param>
        /// <returns>A Vector2 with the position of the tile</returns>
        MathLibrary::Vector2 getPosition(Tile tile);

    protected:
        /// <summary>
        /// Create a tile from a given key. If an actor is created, it is added to the scene.
        /// MODIFY this function to add support for new tiles.
        /// </summary>
        /// <param name="cost">The cost to use</param>
        /// <returns>The actor created</returns>
        Tile createTile(int x, int y, TileKey key);

    private:
        /// <summary>
        /// Generate a new grid of Walls.
        /// </summary>
        void generate(TileKey map[Maze::HEIGHT][Maze::WIDTH]);

    private:
        MathLibrary::Vector2 m_size = { WIDTH, HEIGHT };
        Tile m_grid[WIDTH][HEIGHT];

    };


    Game();

    /// <summary>
    /// Returns the scene at the index given.
    /// Returns an empty scene if the index is out of bounds
    /// </summary>
    /// <param name="index">The index of the desired scene</param>
    /// <returns></returns>
    static Scene* getScene(int index);

    static Game* getInstance() { return m_instance; }

    /// <summary>
    /// Returns the scene that is at the index of the 
    /// current scene index
    /// </summary>
    /// <returns></returns>
    static Scene* getCurrentScene();

    static int getCurrentSceneIndex();

    /// <summary>
    /// Adds the given scene to the array of scenes.
    /// </summary>
    /// <param name="scene">The scene that will be added to the array</param>
    /// <returns>The index the scene was placed at. Returns -1 if
    /// the scene is null</returns>
    static int addScene(Scene* scene);

    /// <summary>
    /// Finds the instance of the scene given that inside of the array
    /// and removes it
    /// </summary>
    /// <param name="scene">The scene that will be removed</param>
    /// <returns>If the scene was successfully removed</returns>
    static bool removeScene(Scene* scene);


    /// <summary>
    /// Sets the current scene in the game to be the scene at the given index
    /// </summary>
    /// <param name="index">The index of the scene to switch to</param>
    static void setCurrentScene(int index);


    /// <summary>
    /// Returns true while a key is being pressed
    /// </summary>
    /// <param name="key">The ascii value of the key to check</param>
    /// <returns></returns>
    static bool getKeyDown(int key);

    /// <summary>
    /// Returns true while if key was pressed once
    /// </summary>
    /// <param name="key">The ascii value of the key to check</param>
    /// <returns></returns>
    static bool getKeyPressed(int key);

    static int getScreenWidth() { return m_screenWidth; }
    static int getScreenHeight() { return m_screenHeight; }

    static void destroy(Actor* actor);
    static void setGameOver(bool value);
    static MathLibrary::Matrix3* getWorld();
    void run();

private:
	void start();
	void update(float delaTime);
	void draw();
	void end();

private:
    Camera2D* m_camera;
    static bool m_gameOver;
	static Scene** m_scenes;
    static int m_sceneCount;
    static int m_currentSceneIndex;
    static int m_screenHeight;
    static int m_screenWidth;

    static Game* m_instance;
};