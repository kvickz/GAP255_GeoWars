//Game.h

#ifndef GAME_H
#define GAME_H

#include "EventListener.h"

#include "Vector3.h"
#include <vector>
#include <string>
#include <queue>

#include <cml/cml.h>

class CollisionSystem;
class EventSystem;
class SpawnManager;
class AssetManager;
class InputManager;
class GameObject;
class Renderer;
class Time;

typedef unsigned int GLuint;
typedef int GLint;

class Game : public EventListener
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

    unsigned int m_numOfWalls;
    unsigned int m_currentScore;

    std::vector<GameObject*> m_gameObjects;
    std::queue<GameObject*> m_gameObjectsToDelete;
    GameObject* m_pCamera;
    GameObject* m_pPlayer;

    Renderer* m_pRenderer;
    EventSystem* m_pEventSystem;
    CollisionSystem* m_pCollisionSystem;
    AssetManager* m_pAssetManager;
    InputManager* m_pInputManager;
    Time* m_pTime;

	//TODO: Maybe make a level class? No plan for other levels though
	LevelBoundary m_levelBoundaries;

    SpawnManager* m_pEnemySpawner;

    virtual void OnEvent(Event* pEvent) override;

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
    
    EventSystem* const GetEventSystem() { return m_pEventSystem; }

private:
	//CreatingGameObjects helper funcs
    void RegisterForEvents();
	void InitLevelBoundaries();
	void CreatePlayer();
	void CreateCamera();
	void CreateEnemy(float x, float y);
    void CreateWall(std::string meshKey, float pointA_x, float pointA_y, float pointB_x, float pointB_y, float height);

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