//GameObjectFactory.h

#ifndef GAMEOBJECTFACTORY_H
#define GAMEOBJECTFACTORY_H

#include "GameObject.h"

#include "Constants.h"

#include <vector>

class Game;
class Renderer;
class CollisionSystem;
class AssetManager;
class Time;

class GameObjectFactory
{
private:
    AssetManager* const k_pAssetManager;
    CollisionSystem* const k_pCollisionSystem;
    Renderer* const k_pRenderer;
    Time* const k_pTime;

public:
    GameObjectFactory(Renderer* const pRenderer, Time* const pTime, CollisionSystem* const pCollisionSystem, AssetManager* const pAssetManager);

    GameObject* CreatePlanet(Game* pGame);
    GameObject* CreateCamera(Game* pGame);
    GameObject* CreatePlayer(Game* pGame);
	GameObject* CreateEnemy(Game* pGame, GameObject* pTarget);
    GameObject* CreateWall(Game* pGame, std::vector<float> vertices, std::vector<unsigned int> indices);
};
#endif // !GAMEOBJECTFACTORY_H