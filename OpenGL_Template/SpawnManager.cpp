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

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
SpawnManager::SpawnManager(Game* pGame, Renderer* pRenderer, Time* pTime, AssetManager* pAssetManager)
    :m_pGame(pGame)
    , m_pTime(pTime)
    , m_pRenderer(pRenderer)
    , m_pAssetManager(pAssetManager)
    , k_enemySpawnPositionCount(4)
    , m_enemySpawnInterval(10)
    , m_enemySpawnIndex(0)
    , m_enemyTimer(0)
{
    CreateEnemySpawns();

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
    delete m_pEnemySpawnPositions;
    m_pEnemySpawnPositions = nullptr;

    m_pGame = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Manager Update Function
//      -Runs a timer that spawns an enemy at a preset spawn point once
//       the timer reaches zero, it then resets and keeps going.
//-------------------------------------------------------------------------------------- -
void SpawnManager::Update()
{
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

        m_pGame->AddGameObject(SpawnEnemy(m_pEnemySpawnPositions[m_enemySpawnIndex]));
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
    GameObjectFactory factory(m_pRenderer, m_pTime);
    GameObject* m_pCamera = factory.CreateCamera(m_pGame);

    //Set the camera position and rotation
    m_pCamera->GetTransformComponent()->SetPosition(position.x, position.y, position.z);
    //Looking down
    m_pCamera->GetTransformComponent()->SetEulerRotation(rotation.x, rotation.y, rotation.z);

    return m_pCamera;
}

//-------------------------------------------------------------------------------------- -
//  Spawn Player Function
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::SpawnPlayer(Vector3 position)
{
    GameObjectFactory factory(m_pRenderer, m_pTime);
    Mesh* pShipMesh = m_pAssetManager->LoadMesh("Models/Ship.obj");
    Color playerColor(0, 0.5f, 1.f);
    //Material* pMaterialPlayer = m_pAssetManager->LoadMaterial("DefaultMaterial", "VertexShader.glsl", "FragmentShader.glsl", playerColor);
    Material* pMaterialPlayer = m_pAssetManager->CreateMaterialInstance("DefaultMaterial");

    //Factory creates player
    GameObject* pPlayer = factory.CreatePlayer(m_pGame);
    RenderComponent* pRenderComponent = pPlayer->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pShipMesh, pMaterialPlayer);
    pRenderComponent->SetColor(playerColor);

    //Position
    pPlayer->GetTransformComponent()->SetPosition(position.x, position.y, position.z);

    return pPlayer;
}

//-------------------------------------------------------------------------------------- -
//  Create Enemy Function
//      -Internal function to handle the logic to create an enemy
//-------------------------------------------------------------------------------------- -
GameObject* SpawnManager::CreateEnemy(float x, float y)
{
    Mesh* pEnemyShipMesh = m_pAssetManager->LoadMesh("Models/Ship_Enemy.obj");

    //Create color
    Color enemyColor(1.f / (float)(rand() % 5 + 1), 0, 0);
    Color defaultColor = Color::m_colors[ColorPreset::k_red];

    //Material* pMaterialEnemy = m_pAssetManager->LoadMaterial("EnemyMaterial", "VertexShader.glsl", "FragmentShader.glsl", defaultColor);
    Material* pMaterialEnemy = m_pAssetManager->CreateMaterialInstance("EnemyMaterial");

    //Factory creates enemy
    GameObjectFactory factory(m_pRenderer, m_pTime);
    GameObject* pEnemy = factory.CreateEnemy(m_pGame, m_pGame->GetPlayerPointer());
    RenderComponent* pRenderComponent = pEnemy->GetComponent<RenderComponent>(k_renderComponentID);
    pRenderComponent->Init(pEnemyShipMesh, pMaterialEnemy);
    pRenderComponent->SetColor(enemyColor);

    //Set position
    Vector3 enemyPos(x, 0.f, y);
    pEnemy->GetTransformComponent()->SetPosition(enemyPos.x, enemyPos.y, enemyPos.z);

    float scale = 1.0f / ((float)(rand() % 4));
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
        Vector3(0, 0, 50)
            , Vector3(0, 0, -50)
            , Vector3(-50, 0, 0)
            , Vector3(50, 0, 0)
    };
}