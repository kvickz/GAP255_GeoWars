//Game.h

#ifndef GAME_H
#define GAME_H

#include "Vector3.h"
#include <vector>
#include <queue>

#include <cml/cml.h>

class CollisionSystem;
class SpawnManager;
class AssetManager;
class InputManager;
class GameObject;
class Renderer;
class Time;

typedef unsigned int GLuint;
typedef int GLint;

class Game
{
public:
	struct LevelBoundary
	{
		float left;
		float right;
		float top;
		float bottom;
	};

private:

    bool m_running;

    std::vector<GameObject*> m_gameObjects;
    std::queue<GameObject*> m_gameObjectsToDelete;
    GameObject* m_pCamera;
    GameObject* m_pPlayer;

    Renderer* m_pRenderer;
    CollisionSystem* m_pCollisionSystem;
    AssetManager* m_pAssetManager;
    InputManager* m_pInputManager;
    Time* m_pTime;

	//TODO: Maybe make a level class? No plan for other levels though
	LevelBoundary m_levelBoundaries;

    SpawnManager* m_pEnemySpawner;

public:
    Game();
    ~Game();

    void Init();
    int Update();
    void Shutdown();

	GameObject* GetCameraObject() { return m_pCamera; }
	const LevelBoundary* GetLevelBoundaries() const { return &m_levelBoundaries; }

    GameObject* AddGameObject(GameObject* pObject);
    GameObject* GetPlayerPointer() { return m_pPlayer; }

private:
	//CreatingGameObjects helper funcs
	void InitLevelBoundaries();
	void CreatePlayer();
	void CreateCamera();
	void CreateEnemy(float x, float y);
    void CreateWall(float pointA_x, float pointA_y, float pointB_x, float pointB_y, float height);

    void UpdateGameLogic();
    void CreateGameObjects();
	void InitializeGameObjects();
    void UpdateGameObjects();
    void RemoveGameObject(GameObject* pGameObject);
    void DeleteQueuedObjects();

    //This is a shutdown function
    void DeleteAllObjects();
};

#endif // !GAME_H