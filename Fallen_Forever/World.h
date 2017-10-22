#pragma once
#include "GlobalDefines.h""
#include <vector>
#include "SFML/System/Clock.hpp"

class Game;
class GameObject;
class ResourceHolder;
class Controller;

class World
{
public:
	World(Game* _Game);
	~World() {};
	
	void Tick(sf::Time _DeltaTime);
	void RenderTick();
	void ControllerTick(sf::Time _DeltaTime);

	GameObject* GetWorldRoot(GameObject*) { return mWorldRoot; }
	ResourceHolder* GetResourceHolder(ResourceHolder*) { return mResourceHolder; }

private:
	void Initialize() {};
	
	Game* mGame;

	GameObject* mWorldRoot;

	ResourceHolder* mResourceHolder;

	std::vector<std::vector<GameObject*>> mGameObjects;

};