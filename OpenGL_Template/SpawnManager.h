//SpawnManager.h

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "Vector3.h"

#include <vector>

class Game;
class GameObject;
class GameObjectFactory;
class AssetManager;
class CollisionSystem;
class Renderer;
class Time;

class SpawnManager
{
private:
    Game* m_pGame;
    Renderer* m_pRenderer;
    AssetManager* m_pAssetManager;
    CollisionSystem* m_pCollisionSystem;
    GameObjectFactory* m_pGameObjectFactory;
    
    Time* m_pTime;

    unsigned int m_enemyTimer;
    unsigned int m_enemySpawnInterval;
    unsigned int m_enemySpawnIndex;
    const unsigned int k_enemySpawnPositionCount;
    Vector3* m_pEnemySpawnPositions;

public:
    SpawnManager(Game* pGame, Renderer* pRenderer, Time* pTime, AssetManager* pAssetManager, CollisionSystem* pCollisionSystem);
    ~SpawnManager();

    void Update();

    GameObject* SpawnEnemy(Vector3 position);
    GameObject* SpawnEnemy(float x, float y, float z);
    GameObject* SpawnEnemy(const unsigned int index);

    GameObject* SpawnCamera(Vector3 position, Vector3 rotation);
    GameObject* SpawnWall(std::vector<float> vertices, std::vector<unsigned int> indices);

    GameObject* SpawnPlayer(Vector3 position);

private:
    GameObject* CreateEnemy(float x, float y);
    void CreateEnemySpawns();
};

#endif // !SPAWNMANAGER_H
