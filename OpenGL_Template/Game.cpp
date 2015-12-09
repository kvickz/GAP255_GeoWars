//Game.cpp

#include "Game.h"
#include "Renderer.h"
#include "AssetManager.h"
#include "InputManager.h"
#include "SpawnManager.h"
#include "FileLoader.h"
#include "Time.h"

#include "GameObject.h"
#include "Vector3.h"

#include <math.h>

Game::Game()
    :m_running(true)
    , m_pRenderer(nullptr)
    , m_pAssetManager(nullptr)
    , m_pInputManager(nullptr)
    , m_pEnemySpawner(nullptr)
    , m_pCamera(nullptr)
    , m_pTime(nullptr)
    , m_pPlayer(nullptr)
{
    //
}

Game::~Game()
{
    delete m_pRenderer;
    m_pRenderer = nullptr;

    delete m_pAssetManager;
    m_pAssetManager = nullptr;

    delete m_pInputManager;
    m_pInputManager = nullptr;

    delete m_pTime;
    m_pTime = nullptr;

    delete m_pEnemySpawner;
    m_pEnemySpawner = nullptr;

    m_pCamera = nullptr;
}

#include "RenderComponent.h"

//-------------------------------------------------------------------------------------- -
//  Main Game Initialization Function
//      -Initializes all of the main systems of the game
//      -Loads all necessary data and creates all the initial game objects
//-------------------------------------------------------------------------------------- -
void Game::Init()
{
    m_pRenderer = new Renderer();
    m_pRenderer->Init();

    m_pTime = new Time();
    m_pAssetManager = new AssetManager();
    m_pInputManager = new InputManager(this);
    m_pEnemySpawner = new SpawnManager(this, m_pRenderer, m_pTime, m_pAssetManager);
    
    CreateGameObjects();
	InitializeGameObjects();
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

    const int k_numOfEnemies = 10;
    for (int i = 0; i < k_numOfEnemies; ++i)
	{
		CreateEnemy(rand() % 30 * 5.f - 15, rand() % 30 * 1.5f);
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
    UpdateGameObjects();
    UpdateGameLogic();

    m_pRenderer->SwapWindow();

    //Remove Queued objects
    DeleteQueuedObjects();

    return 1;   //SUCCESS
}

//-------------------------------------------------------------------------------------- -
//  Update Game Logic Function
//      -Runs any custom game logic
//-------------------------------------------------------------------------------------- -
void Game::UpdateGameLogic()
{
    m_pEnemySpawner->Update();
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
void Game::InitLevelBoundaries()
{
	//TODO: This kinda sucks
	const int k_halfLevelWidth = 80;
	const int k_halfLevelHeight = 50;
	m_levelBoundaries.left = -k_halfLevelWidth;
	m_levelBoundaries.right = k_halfLevelWidth;
	m_levelBoundaries.top = k_halfLevelHeight;
	m_levelBoundaries.bottom = -k_halfLevelHeight;
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
    //Create
    m_pCamera = AddGameObject(m_pEnemySpawner->SpawnCamera(Vector3(0, 180, 0), Vector3(-1.55f, 0, 0)));
}

//**************************
//	Creating Enemy
//**************************
void Game::CreateEnemy(float x, float y)
{
    //Create
    AddGameObject(m_pEnemySpawner->SpawnEnemy(x, 0, y));
}

GameObject* Game::AddGameObject(GameObject* pObject)
{
    m_gameObjects.push_back(pObject);

    return pObject;
}