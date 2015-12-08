//Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <queue>

#include <cml/cml.h>

class Renderer;
class AssetManager;
class InputManager;
class GameObject;
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
    AssetManager* m_pAssetManager;
    InputManager* m_pInputManager;
    Time* m_pTime;

	//TODO: Maybe make a level class? No plan for other levels though
	LevelBoundary m_levelBoundaries;

public:
    Game();
    ~Game();

    void Init();
    int Update();
    void Shutdown();

	GameObject* GetCameraObject() { return m_pCamera; }
	const LevelBoundary* GetLevelBoundaries() const { return &m_levelBoundaries; }

private:
	//CreatingGameObjects helper funcs
	void InitLevelBoundaries();
	void CreatePlayer();
	void CreateCamera();
	void CreateEnemy(float x, float y);

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