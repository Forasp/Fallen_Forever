#include "World.h"
#include "Game.h"
#include "GameObject.h"
#include "Controller.h"
#include "Messenger.h"
#include "Message.h"

World::World(Game* _Game)
{
	mGame = _Game;

	mGameObjects.resize(NUMBER_OF_LAYERS);
	mGame->GetMessenger("KeyEvents").get()->AddListener(this);

	// Construct our world here.
}

/// <summary> 
/// Calls RenderTick on graphics scenegraph.
/// </summary>
void World::RenderTick(sf::RenderWindow* _RenderWindow)
{
	for (std::vector<std::shared_ptr<GameObject>> goVector : mGameObjects)
	{
		for (std::shared_ptr<GameObject> go : goVector)
		{
			go.get()->RenderTick(_RenderWindow);
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
	if (_OverrideControl == sf::Keyboard::Escape)
	{
		mGame->QueueMessage("GlobalEvents", std::make_unique<Message>(MESSAGE_TYPE_QUIT, "Escape key pressed."));
	}
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void World::ReadMessage(Message* _Message)
{
	switch (_Message->GetMessageType())
	{
	case MESSAGE_TYPE_INVALID:
		return;
		break;
	case MESSAGE_TYPE_INPUT:
		CheckControls(_Message->GetMessageDouble());
		break;
	case MESSAGE_TYPE_DOUBLE:

		break;
	case MESSAGE_TYPE_STRING:

		break;
	default:

		break;
	}
}

/// <summary> 
/// Adds a reference to a game object into our rendering list
/// </summary>
void World::AddGlobalReferenceToObject(std::shared_ptr<GameObject> _GameObject, int _Layer)
{
	// Early out if invalid layer or _GameObject is null pointer
	if (_Layer >= NUMBER_OF_LAYERS || _GameObject == nullptr)
	{
		return;
	}
	
	// Early out if matching game object found
	for (std::vector<std::shared_ptr<GameObject>> outer_iterator : mGameObjects)
	{
		for (std::shared_ptr<GameObject> inner_iterator : outer_iterator)
		{
			if (inner_iterator == _GameObject)
			{
				return;
			}
		}
	}

	// Add object to appropriate layer.
	mGameObjects[_Layer].push_back(_GameObject);
}