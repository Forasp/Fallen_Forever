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
	for (std::vector<std::shared_ptr<GameObject>> goVector : mGameObjects)
	{
		for (std::shared_ptr<GameObject> go : goVector)
		{
			go.get()->RenderTick();
		}
	}
}

void World::Tick(sf::Time _DeltaTime)
{
	mWorldRoot.get()->Tick(_DeltaTime);
}

void World::ControllerTick(sf::Time _DeltaTime)
{
	mWorldRoot.get()->ControllerTick(_DeltaTime);
}

void World::CheckControls()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		// Pass message to quit
	}
}