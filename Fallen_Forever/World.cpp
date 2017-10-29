#include "World.h"
#include "Game.h"
#include "GameObject.h"
#include "Controller.h"
#include "Messenger.h"

World::World(Game* _Game)
{
	mGame = _Game;

	mGameObjects.resize(NUMBER_OF_LAYERS);

	// Construct our world here.
}

/// <summary> 
/// Calls RenderTick on graphics scenegraph.
/// </summary>
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

/// <summary> 
/// Ticks all objects in traditional scene graph.
/// </summary>
void World::Tick(sf::Time _DeltaTime)
{
	mWorldRoot.get()->Tick(_DeltaTime);
}

/// <summary> 
/// Checks controls and ticks all controllers.
/// </summary>
void World::ControllerTick(sf::Time _DeltaTime)
{
	CheckControls();
	mWorldRoot.get()->ControllerTick(_DeltaTime);
}

/// <summary> 
/// Checks only for controls expected by the world.
/// </summary>
void World::CheckControls(int _OverrideControl)
{
	// If the escape key has been pressed, pass the message onto the key events.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || _OverrideControl == sf::Keyboard::Escape)
	{
		mGame->GetMessenger("KeyEvents").get()->ReceiveMessage(Message(MESSAGE_TYPE_INPUT, sf::Keyboard::Escape));
	}
}