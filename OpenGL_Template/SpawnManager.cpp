//SpawnManager.cpp

#include "SpawnManager.h"

#include "GameObjectFactory.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Time.h"
#include "Game.h"

#include "EventSystem.h"
#include "Event.h"

#include "Macros.h"

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
SpawnManager::SpawnManager(Game* pGame, Renderer* pRenderer, Time* pTime, AssetManager* pAssetManager, AudioManager* const pAudioManager, CollisionSystem* pCollisionSystem)
    :m_pGame(pGame)
    , m_pTime(pTime)
    , m_pRenderer(pRenderer)
    , m_pAssetManager(pAssetManager)
    , k_pAudioManager(pAudioManager)
    , m_pCollisionSystem(pCollisionSystem)
    , k_enemySpawnPositionCount(4)
    , m_enemySpawnInterval(50)
    , m_enemySpawnIndex(0)
    , m_enemySpawnLimit(55)
    , m_enemySpawnCount(0)
    , m_enemyTimer(0)
    , m_enemiesSpawningActive(true)
{
    RegisterForEvents();

    CreateEnemySpawns();

    //Create Factory
    m_pGameObjectFactory = new GameObjectFactory(pRenderer, pTime, pCollisionSystem, m_pAssetManager, this, k_pAudioManager);

    //Load Necessary Materials
    Color playerDefaultColor(0, 0.5f, 1.f);
    m_pAssetManager->LoadMaterial("DefaultMaterial", "VertexShader.glsl", "FragmentShader.glsl", playerDefaultColor);

    Color enemyDefaultColor = Color::m_colors[ColorPreset::k_red];
    m_pAssetManager->LoadMaterial("EnemyMaterial", "VertexShader.glsl", "FragmentShader.glsl", enemyDefaultColor);
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
SpawnManager::~SpawnManager()
{
    m_pGame->GetEventSystem()->RemoveListener(k_playerDeathEvent, this);
    m_pGame->GetEventSystem()->RemoveListener(k_enemyDeathEvent, this);

    SAFE_DELETE(m_pEnemySpawnPositions);
    SAFE_DELETE(m_pGameObjectFactory);

    m_pGame = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Manager Update Function
//      -Runs a timer that spawns an enemy at a preset spawn point once
//       the timer reaches zero, it then resets and keeps going.
//-------------------------------------------------------------------------------------- -
void SpawnManager::Update()
{
    //If this is active, enemies will spawn
    if (!m_enemiesSpawningActive)
        return;

    //Spawning enemies at 'timed' intervals, currently framerate dependent
    ++m_enemyTimer;

    //if timer exceeds the timer limit, spawn an enemy
    if (m_enemyTimer > m_enemySpawnInterval)
    {
        //Reset timer
        m_enemyTimer = 0;

        //Iterator the spawn index
        ++m_enemySpawnIndex;

        //Reset spawn index if it passes the limit
        if (m_enemySpawnIndex >= k_enemySpawnPositionCount)
            m_enemySpawnIndex = 0;

        //Spawn Enemy
        if (m_enemySpawnCount < m_enemySpawnLimit) 
        {
            m_pGame->AddGameObject(SpawnEnemy(m_pEnemySpawnPositions[m_enemySpawnIndex]));
        }
    }
}

//-------------------------------------------------------------------------------------- -
//  Register For Events Function
//-------------------------------------------------------------------------------------- -
void SpawnManager::RegisterForEvents()
{
    m_pGame->GetEventSystem()->RegisterListener(k_playerDeathEvent, this);
    m_pGame->GetEventSystem()->RegisterListener(k_enemyDeathEvent, this);
}

//-------------------------------------------------------------------------------------- -
//  On Event Function
//-------------------------------------------------------------------------------------- -
void SpawnManager::OnEvent(Event* pEvent)
{
    switch (pEvent->GetEventID())
    {
    case k_playerDeathEvent:
        m_enemiesSpawningActive = false;

    case k_enemyDeathEvent:
        DecreaseSpawnCounter();
        //SpawnDeathParticles(static_cast<EnemyDeathEvent*>(pEvent)->GetLocation());
        break;
    }
}

void SpawnManager::SpawnDeathParticles(Vector3 position)
{
    //Spawn particles
    const int k_numOfParticles = 15;
    for (int i = 0; i < k_numOfParticles; ++i)
    {
        m_pGame->AddGameObject(SpawnParticle(position));
    }
    
}

//-------------------------------------------------------------------------------------- -
//  Spawn Enemy Functions
//      -These take in position values which feed into the internal CreateEnemy() to
//       reduce the duplication of code.
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnEnemy(Vector3 position)
{
    return CreateEnemy(position.x, position.z);
}

GameObject* SpawnManager::SpawnEnemy(float x, float y, float z)
{
    return CreateEnemy(x, z);
}

GameObject* SpawnManager::SpawnEnemy(const unsigned int index)
{
    float x = m_pEnemySpawnPositions[index].x;
    float y = m_pEnemySpawnPositions[index].z;
    return CreateEnemy(x, y);
}

//-------------------------------------------------------------------------------------- -
//  Spawn Camera Function
//      -Spawns a camera!
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnCamera(Vector3 position, Vector3 rotation)
{
    //Create Camera
    GameObject* pCamera = m_pGameObjectFactory->CreateCamera(m_pGame);

    //Set the camera position and rotation
    pCamera->GetTransformComponent()->SetPosition(position.x, position.y, position.z);
    //Looking down
    pCamera->GetTransformComponent()->SetEulerRotation(rotation.x, rotation.y, rotation.z);

    return pCamera;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Wall Function
//      -Spawns a wall!
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnWall(std::string meshKey, std::vector<float> vertices, std::vector<unsigned int> indices)
{
    //Create Wall
    GameObject* pWall = m_pGameObjectFactory->CreateWall(m_pGame, vertices, indices);

    Mesh* pWallMesh = m_pAssetManager->GenerateQuad(meshKey, vertices, indices);
    Material* pMaterialWall = m_pAssetManager->CreateMaterialInstance("EnemyMaterial");

    RenderComponent* pRenderComponent = pWall->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pWallMesh, pMaterialWall);

    pRenderComponent->SetColor(Color(0.f, 0.5f, 0.7f));

    return pWall;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Player Function
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnPlayer(Vector3 position)
{
    Mesh* pShipMesh = m_pAssetManager->LoadMesh("Models/Ship.obj");
    Color playerColor(0, 0.5f, 0.7f);
    //Material* pMaterialPlayer = m_pAssetManager->LoadMaterial("DefaultMaterial", "VertexShader.glsl", "FragmentShader.glsl", playerColor);
    Material* pMaterialPlayer = m_pAssetManager->CreateMaterialInstance("DefaultMaterial");

    //Factory creates player
    GameObject* pPlayer = m_pGameObjectFactory->CreatePlayer(m_pGame);
    RenderComponent* pRenderComponent = pPlayer->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pShipMesh, pMaterialPlayer);
    pRenderComponent->SetColor(playerColor);

    //Position
    pPlayer->GetTransformComponent()->SetPosition(position.x, position.y, position.z);

    return pPlayer;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Particle Function
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnParticle(Vector3 position)
{
    Mesh* pParticleMesh = m_pAssetManager->LoadMesh("Models/Particle1.obj");
    Color particleColor(0.5f, 0.5f, 0.9f);
    Material* pMaterialParticle = m_pAssetManager->CreateMaterialInstance("DefaultMaterial");

    GameObject* pParticleObject = m_pGameObjectFactory->CreateParticle(m_pGame);
    RenderComponent* pRenderComponent = pParticleObject->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pParticleMesh, pMaterialParticle);
    pRenderComponent->SetColor(particleColor);

    //Position
    pParticleObject->GetTransformComponent()->SetPosition(position.x, position.y, position.z);

    return pParticleObject;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Bullet Function
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnBullet(Vector3 position)
{
    Mesh* pParticleMesh = m_pAssetManager->LoadMesh("Models/Bullet.obj");
    Color particleColor(1.0f, 0.5f, 0.5f);
    Material* pMaterialParticle = m_pAssetManager->CreateMaterialInstance("DefaultMaterial");

    GameObject* pBulletObject = m_pGameObjectFactory->CreateBullet(m_pGame);
    RenderComponent* pRenderComponent = pBulletObject->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pParticleMesh, pMaterialParticle);
    pRenderComponent->SetColor(particleColor);

    //Position
    pBulletObject->GetTransformComponent()->SetPosition(position.x, position.y, position.z);

    m_pGame->AddGameObject(pBulletObject);
    return pBulletObject;
}

//-------------------------------------------------------------------------------------- -
//  Create Enemy Function
//      -Internal function to handle the logic to create an enemy
//-------------------------------------------------------------------------------------- -

#include "EnemyAIComponent.h"

GameObject* SpawnManager::CreateEnemy(float x, float y)
{
    IncreaseSpawnCounter();

    Mesh* pEnemyShipMesh = m_pAssetManager->LoadMesh("Models/Ship_Enemy.obj");
    Material* pMaterialEnemy = m_pAssetManager->CreateMaterialInstance("EnemyMaterial");

    //Factory creates enemy
    GameObject* pEnemy = m_pGameObjectFactory->CreateEnemy(m_pGame, m_pGame->GetPlayerPointer());
    RenderComponent* pRenderComponent = pEnemy->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pEnemyShipMesh, pMaterialEnemy);

    //Create color
    float randColorVal = 1.f / (float)((rand() % 5) + 1) * 5;
    Color enemyColor;

    //Randomize Enemy Type
    EnemyAIComponent* pAIComponent = pEnemy->GetComponent<EnemyAIComponent>(k_enemyAIComponentID);
    int randVal = rand() % 2;

    //randVal = 1;

    //Assigning enemy Type
    if (randVal == 0)
    {
        pAIComponent->SetBehavior(EnemyBehaviorType::k_chaser);
        enemyColor.r = randColorVal;
    }
    else
    {
        pAIComponent->SetBehavior(EnemyBehaviorType::k_floater);
        enemyColor.r = randColorVal / 3;
        enemyColor.g = 1.0f;
    }

    //Assign Color
    pRenderComponent->SetColor(enemyColor);

    //Set position
    Vector3 enemyPos(x, 0.f, y);
    pEnemy->GetTransformComponent()->SetPosition(enemyPos.x, enemyPos.y, enemyPos.z);

    float scale = 1.0f / ((float)((rand() % 4) + 1) * 1);
    pEnemy->GetTransformComponent()->Scale(scale, scale, scale);

    return pEnemy;
}

//-------------------------------------------------------------------------------------- -
//  Create Enemy Spawns Function
//      -Initializes the spawn positions for enemies
//-------------------------------------------------------------------------------------- -
void SpawnManager::CreateEnemySpawns()
{
    m_pEnemySpawnPositions = new Vector3[k_enemySpawnPositionCount]
    {
        Vector3(70, 0, 50)
            , Vector3(70, 0, -50)
            , Vector3(-70, 0, -50)
            , Vector3(-70, 0, 50)
    };
}

void SpawnManager::DecreaseSpawnCounter()
{ 
    --m_enemySpawnCount; 
}

void SpawnManager::IncreaseSpawnCounter()
{ 
    ++m_enemySpawnCount; 
}