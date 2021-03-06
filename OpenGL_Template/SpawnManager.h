//SpawnManager.h

#ifndef SPAWNMANAGER_H
#define SPAWNMANAGER_H

#include "EventListener.h"

#include "Vector3.h"

#include <vector>
#include <string>

class Game;
class GameObject;
class GameObjectFactory;
class AssetManager;
class AudioManager;
class CollisionSystem;
class Renderer;
class Time;

class SpawnManager : public EventListener
{
private:
    bool m_enemiesSpawningActive;

    Game* m_pGame;
    Renderer* m_pRenderer;
    AssetManager* m_pAssetManager;
    AudioManager* const k_pAudioManager;
    CollisionSystem* m_pCollisionSystem;
    GameObjectFactory* m_pGameObjectFactory;
    
    Time* m_pTime;

    unsigned int m_enemyTimer;
    unsigned int m_enemySpawnInterval;
    unsigned int m_enemySpawnIndex;
    unsigned int m_enemySpawnLimit;
    unsigned int m_enemySpawnCount;
    const unsigned int k_enemySpawnPositionCount;
    Vector3* m_pEnemySpawnPositions;

public:
    SpawnManager(Game* pGame, Renderer* pRenderer, Time* pTime, AssetManager* const pAssetManager, AudioManager* pAudioManager, CollisionSystem* pCollisionSystem);
    ~SpawnManager();

    void Update();

    GameObject* SpawnEnemy(Vector3 position);
    GameObject* SpawnEnemy(float x, float y, float z);
    GameObject* SpawnEnemy(const unsigned int index);
    GameObject* SpawnCamera(Vector3 position, Vector3 rotation);
    GameObject* SpawnWall(std::string meshKey, std::vector<float> vertices, std::vector<unsigned int> indices);
    GameObject* SpawnPlayer(Vector3 position);
    GameObject* SpawnParticle(Vector3 position);
    GameObject* SpawnBullet(Vector3 position);
    
    void SpawnDeathParticles(Vector3 position);

    virtual void OnEvent(Event* pEvent) override;

private:
    GameObject* CreateEnemy(float x, float y);
    void RegisterForEvents();
    void CreateEnemySpawns();
    void DecreaseSpawnCounter();
    void IncreaseSpawnCounter();
};

#endif // !SPAWNMANAGER_H
