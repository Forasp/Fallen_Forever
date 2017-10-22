#include "World.h"
#include "Game.h"
#include "GameObject.h"
#include "Controller.h"

World::World(Game* _Game)
{
	mGame = _Game;

	mGameObjects.resize(NUMBER_OF_LAYERS);

	// Construct our world here.
}

void World::RenderTick()
{
	for (std::vector<GameObject*> goVector : mGameObjects)
	{
		for (GameObject* go : goVector)
		{
			go->RenderTick();
		}
	}
}

void World::Tick(sf::Time _DeltaTime)
{
	mWorldRoot->Tick(_DeltaTime);
}

void World::ControllerTick(sf::Time _DeltaTime)
{
	mWorldRoot->ControllerTick(_DeltaTime);
}