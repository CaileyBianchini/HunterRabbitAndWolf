#pragma once
#include "Scene.h"
class Camera2D;

static class Game
{
public:
    Game();
    /// <summary>
    /// Returns the scene at the index given.
    /// Returns an empty scene if the index is out of bounds
    /// </summary>
    /// <param name="index">The index of the desired scene</param>
    /// <returns></returns>
    static Scene* getScene(int index);


    /// <summary>
    /// Returns the scene that is at the index of the 
    /// current scene index
    /// </summary>
    /// <returns></returns>
    static Scene* getCurrentScene();

    /// <returns>The index of the current scene in the game's array of scenes.</returns>
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

    /// <summary>
    /// Removes the actor from the scene, removes it from its parent, calls its end function, and deletes the actor.
    /// </summary>
    /// <param name="actor">The actor that will be deleted.</param>
    static void destroy(Actor* actor);

    /// <summary>
    /// Sets the game state to be the given value. If true, the game will end.
    /// </summary>
    /// <param name="value">The value to set game over.</param>
    static void setGameOver(bool value);

    /// <returns>The world matrix of the current scene.</returns>
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
};