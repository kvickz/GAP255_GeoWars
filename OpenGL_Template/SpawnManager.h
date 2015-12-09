//SpawnManager.h

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "Vector3.h"

class Game;
class GameObject;
class AssetManager;
class Renderer;
class Time;

class SpawnManager
{
private:
    Game* m_pGame;
    Renderer* m_pRenderer;
    AssetManager* m_pAssetManager;
    
    Time* m_pTime;

    unsigned int m_enemyTimer;
    unsigned int m_enemySpawnInterval;
    unsigned int m_enemySpawnIndex;
    const unsigned int k_enemySpawnPositionCount;
    Vector3* m_pEnemySpawnPositions;

public:
    SpawnManager(Game* pGame, Renderer* pRenderer, Time* pTime, AssetManager* pAssetManager);
    ~SpawnManager();

    void Update();

    GameObject* SpawnEnemy(Vector3 position);
    GameObject* SpawnEnemy(float x, float y, float z);
    GameObject* SpawnEnemy(const unsigned int index);

    GameObject* SpawnCamera(Vector3 position, Vector3 rotation);

    GameObject* SpawnPlayer(Vector3 position);

private:
    GameObject* CreateEnemy(float x, float y);
    void CreateEnemySpawns();
};

#endif // !SPAWNMANAGER_H
