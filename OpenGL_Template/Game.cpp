//Game.cpp

#include "Game.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "SpawnManager.h"
#include "CollisionSystem.h"
#include "EventSystem.h"
#include "Event.h"
#include "FileLoader.h"
#include "Time.h"

#include "Mesh.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "Vector3.h"

#include "Macros.h"

#include <math.h>

//-------------------------------------------------------------------------------------- -
//  Constructor
//-------------------------------------------------------------------------------------- -
Game::Game()
    :m_running(true)
    , m_pRenderer(nullptr)
    , m_pAssetManager(nullptr)
    , m_pInputManager(nullptr)
    , m_pEnemySpawner(nullptr)
    , m_pCollisionSystem(nullptr)
    , m_pEventSystem(nullptr)
    , m_pCamera(nullptr)
    , m_pTime(nullptr)
    , m_pPlayer(nullptr)
    , m_numOfWalls(0)
    , m_currentScore(0)
{
    //
}

//-------------------------------------------------------------------------------------- -
//  Destructor
//-------------------------------------------------------------------------------------- -
Game::~Game()
{
    SAFE_DELETE(m_pRenderer);
    SAFE_DELETE(m_pAssetManager);
    SAFE_DELETE(m_pInputManager);
    SAFE_DELETE(m_pTime);
    SAFE_DELETE(m_pEnemySpawner);
    SAFE_DELETE(m_pCollisionSystem);
    SAFE_DELETE(m_pEventSystem);

    m_pCamera = nullptr;
}

//-------------------------------------------------------------------------------------- -
//  Main Game Initialization Function
//      -Initializes all of the main systems of the game
//      -Loads all necessary data and creates all the initial game objects
//-------------------------------------------------------------------------------------- -
void Game::Init()
{
    m_pEventSystem = new EventSystem();
    m_pRenderer = new Renderer();
    m_pRenderer->Init();

    m_pTime = new Time();
    m_pAssetManager = new AssetManager();
    m_pInputManager = new InputManager(this);
    m_pCollisionSystem = new CollisionSystem();
    m_pEnemySpawner = new SpawnManager(this, m_pRenderer, m_pTime, m_pAssetManager, m_pCollisionSystem);

    RegisterForEvents();
    CreateGameObjects();
	InitializeGameObjects();
}

//-------------------------------------------------------------------------------------- -
//  Register For Events Function
//      -Registers for all necessary gameplay events.
//-------------------------------------------------------------------------------------- -
void Game::RegisterForEvents()
{
    m_pEventSystem->RegisterListener(k_playerDeathEvent, this);
    m_pEventSystem->RegisterListener(k_enemyDeathEvent, this);
}

//-------------------------------------------------------------------------------------- -
//  Create Game Objects Function
//      -This is an initialization-phase function that will create
//       all of the initial objects for the game.
//-------------------------------------------------------------------------------------- -
void Game::CreateGameObjects()
{
	InitLevelBoundaries();
	CreatePlayer();
	CreateCamera();

    const int k_numOfEnemies = 55;
    for (int i = 0; i < k_numOfEnemies; ++i)
	{
		//CreateEnemy(rand() % 30 * 5.f - 25, 45.f);
	}
}

//-------------------------------------------------------------------------------------- -
//  Initialize Game Objects Function
//		-Calls init on all game objects
//-------------------------------------------------------------------------------------- -
void Game::InitializeGameObjects()
{
	// Object Initialization
	//INIT ALL GAME OBJECTS
	for (GameObject* pGameObj : m_gameObjects)
	{
		pGameObj->Init();
	}
}

//-------------------------------------------------------------------------------------- -
//  Main Game Update Function
//-------------------------------------------------------------------------------------- -
int Game::Update()
{
    //Calculating time
    m_pTime->Update();

    //TODO: needs to be refactored into renderer/input manager
    if (m_pInputManager->HandleEvents() == 0)  //HANDLING WINDOW EVENTS
        return 0;

    //TODO: I'd like to get this to happen AFTER the game objects update
    //      currently with the game components drawing themselves its a bit wonky
    m_pRenderer->ClearScreen();

    //Updating objs
    UpdateGameLogic();
    UpdateGameObjects();

    m_pRenderer->SwapWindow();

    //Remove Queued objects
    DeleteQueuedObjects();

    return 1;   //SUCCESS
}

//-------------------------------------------------------------------------------------- -
//  On Event Function
//-------------------------------------------------------------------------------------- -

void Game::OnEvent(Event* pEvent)
{
    switch (pEvent->GetEventID())
    {
        case k_playerDeathEvent:
        {
            int debug = 0;
            break;
        }
        case k_enemyDeathEvent:
        {
            m_currentScore += 50;
            break;
        }
    }
}

//-------------------------------------------------------------------------------------- -
//  Update Game Logic Function
//      -Runs any custom game logic
//-------------------------------------------------------------------------------------- -
void Game::UpdateGameLogic()
{
    m_pEnemySpawner->Update();
    m_pCollisionSystem->Update();
    
    //float sinVal = sinf(SDL_GetTicks() * 0.0001f) * 0.5f;
    //m_gameObjects[0]->GetTransformComponent()->Translate(sinVal, 0.f, 0.f);
    //m_gameObjects[0]->GetTransformComponent()->Rotate(0.1f, 0.f, 0.f);
}

//-------------------------------------------------------------------------------------- -
//  Update Game Objects Function
//      -Iterates through all gameObjects calling Update() within each.
//      -Also checks for objects that need to be removed
//-------------------------------------------------------------------------------------- -
void Game::UpdateGameObjects()
{
    auto iterator = m_gameObjects.begin();

    while (iterator != m_gameObjects.end())
    {
        (*iterator)->Update();

        //Places object into deletion queue
        if ((*iterator)->IsReadyToDelete())
        {
            m_gameObjectsToDelete.push((*iterator));

            auto tempIterator = iterator;
            ++iterator;

            //TODO: This might not work as expected, if it calls delete on the pointer
            m_gameObjects.erase(tempIterator);

            return; //TODO: This might be a bad idea?
        }

        ++iterator;
    }
}

//-------------------------------------------------------------------------------------- -
//  Remove Game Object Function
//      -Takes a pointer to a game object as a parameter and marks it for deletion.
//       does not actually delete the object. 
//      -Deletion of objects is handled by Game::DeleteQueuedObjects()
//-------------------------------------------------------------------------------------- -
void Game::RemoveGameObject(GameObject* pGameObject)
{
    pGameObject->DeleteObject();
}

//-------------------------------------------------------------------------------------- -
//  Delete Queued Game Objects Function
//      -Will destroy any objects inside m_gameObjectsToDelete for good.
//-------------------------------------------------------------------------------------- -
void Game::DeleteQueuedObjects()
{
    while (!m_gameObjectsToDelete.empty())
    {
        //TODO: safe delete macro
        delete m_gameObjectsToDelete.front();
        m_gameObjectsToDelete.front() = nullptr;

        m_gameObjectsToDelete.pop();
    }
}

//-------------------------------------------------------------------------------------- -
//  Main Game Shutdown Function
//-------------------------------------------------------------------------------------- -
void Game::Shutdown()
{
    m_pRenderer->Shutdown();
    DeleteAllObjects();
}

//-------------------------------------------------------------------------------------- -
//  Add Game Object Function
//-------------------------------------------------------------------------------------- -
GameObject* Game::AddGameObject(GameObject* pObject)
{
    m_gameObjects.push_back(pObject);

    return pObject;
}

//-------------------------------------------------------------------------------------- -
//  Delete All Objects Function
//      -Only meant to be called by shutdown, does as the name says
//-------------------------------------------------------------------------------------- -
void Game::DeleteAllObjects()
{
    auto iterator = m_gameObjects.begin();

    while (iterator != m_gameObjects.end())
    {
        delete (*iterator);
        (*iterator) = nullptr;

        ++iterator;
    }
}

//**************************
//	Create the level
//**************************
#include "StringMerger.h"

void Game::InitLevelBoundaries()
{
	const int k_halfLevelWidth = 80;
	const int k_halfLevelHeight = 60;
    const float k_height = 0.1f;
	m_levelBoundaries.left = -k_halfLevelWidth;
	m_levelBoundaries.right = k_halfLevelWidth;
	m_levelBoundaries.top = k_halfLevelHeight;
	m_levelBoundaries.bottom = -k_halfLevelHeight;

    //Creating the level boundaries
    for (int i = 0; i < 1; ++i)
    {
        float distanceBetweenLines = 1.f;
        float left = m_levelBoundaries.left - i * (distanceBetweenLines);
        float right = m_levelBoundaries.right + i * (distanceBetweenLines);
        float top = m_levelBoundaries.top + i * (distanceBetweenLines);
        float bottom = m_levelBoundaries.bottom - i * (distanceBetweenLines);

        const std::string k_wallKey = "WallMesh_";
        
        //Left
        CreateWall(k_wallKey, left, bottom, left, top, k_height);
        //Close
        CreateWall(k_wallKey, left, top, right, top, k_height);
        //Right
        CreateWall(k_wallKey, right, top, right, bottom, k_height);
        //Far
        CreateWall(k_wallKey, right, bottom, left, bottom, k_height);
    }
}

//**************************
//  Creating a wall from...
//                                          Point A                         Point B                         Height
void Game::CreateWall(std::string meshKey, float pointA_x, float pointA_y, float pointB_x, float pointB_y, float height)
{
    //Create Unique key for each wall
    ++m_numOfWalls;
    meshKey = StringMerger::StringWithInt(meshKey, m_numOfWalls);

    std::vector<float> verts;
    std::vector<unsigned int> indices;

    const float k_floor = -0.1f;
    //Creating verts
    //TODO: Find more elegant solution for mesh generation
    //V1
    verts.push_back(pointA_x);
    verts.push_back(k_floor);
    verts.push_back(pointA_y);
    //V2
    verts.push_back(pointA_x);
    verts.push_back(height);
    verts.push_back(pointA_y);
    //V3
    verts.push_back(pointB_x);
    verts.push_back(height);
    verts.push_back(pointB_y);
    //V4
    verts.push_back(pointB_x);
    verts.push_back(k_floor);
    verts.push_back(pointB_y);
    
    //Create indices
    //F1
    indices.push_back(0);
    indices.push_back(1);
    indices.push_back(2);
    //F2
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);

    AddGameObject(m_pEnemySpawner->SpawnWall(meshKey, verts, indices));
}

//**************************
//	Creating the player
//**************************
void Game::CreatePlayer()
{
    //Create
    m_pPlayer = AddGameObject(m_pEnemySpawner->SpawnPlayer(Vector3(0, 0, 0)));
    //Give player control
    m_pInputManager->AddPlayer(0, m_pPlayer);
}

//**************************
//	Creating a camera
//**************************
void Game::CreateCamera()
{
    //Create Camera
    //m_pCamera = AddGameObject(m_pEnemySpawner->SpawnCamera(Vector3(0, 180, 0), Vector3(-1.55f, 0, 0)));
    //m_pCamera = AddGameObject(m_pEnemySpawner->SpawnCamera(Vector3(0, 40, 100), Vector3(-0.35f, 0, 0)));
    m_pCamera = AddGameObject(m_pEnemySpawner->SpawnCamera(Vector3(0, 130, 165), Vector3(-0.67f, 0, 0)));
}

//**************************
//	Creating Enemy
//**************************
void Game::CreateEnemy(float x, float y)
{
    //Create
    AddGameObject(m_pEnemySpawner->SpawnEnemy(x, 0, y));
}