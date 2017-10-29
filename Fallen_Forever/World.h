#pragma once
#include "GlobalDefines.h"
#include <vector>
#include "SFML/System/Clock.hpp"
#include <memory>
#include "Listener.h"

class Game;
class GameObject;
class ResourceHolder;
class Controller;

class World : public Listener
{
public:
	World(Game* _Game);
	~World() {};
	
	void Tick(sf::Time _DeltaTime);
	void RenderTick();
	void ControllerTick(sf::Time _DeltaTime);

	std::shared_ptr<GameObject> GetWorldRoot() { return mWorldRoot; }
	std::shared_ptr<ResourceHolder> GetResourceHolder() { return mResourceHolder; }

private:
	void Initialize() {};

	virtual void CheckControls(int _OverrideControl = -1);
	
	Game* mGame;

	std::shared_ptr<GameObject> mWorldRoot;

	std::shared_ptr<ResourceHolder> mResourceHolder;

	std::vector<std::vector<std::shared_ptr<GameObject>>> mGameObjects;

};