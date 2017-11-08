#pragma once
#include "GlobalDefines.h"
#include <vector>
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
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
	
	virtual void Tick(sf::Time _DeltaTime);
	virtual void RenderTick(sf::RenderWindow* _RenderWindow);
	virtual void ControllerTick(sf::Time _DeltaTime);

	virtual void ReadMessage(Message* _Message);

	virtual std::shared_ptr<GameObject> GetWorldRoot() { return mWorldRoot; }
	virtual std::shared_ptr<ResourceHolder> GetResourceHolder() { return mResourceHolder; }
	virtual void AddGlobalReferenceToObject(std::shared_ptr<GameObject> _GameObject, int _Layer);

private:
	void Initialize() {};

	virtual void CheckControls(int _OverrideControl = -1);
	
	Game* mGame;

	std::shared_ptr<GameObject> mWorldRoot;

	std::shared_ptr<ResourceHolder> mResourceHolder;

	std::vector<std::vector<std::shared_ptr<GameObject>>> mGameObjects;

};