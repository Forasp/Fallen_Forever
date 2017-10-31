#include "Game.h"
#include "World.h"
#include "SFML/Window/Keyboard.hpp"
#include "Message.h"
#include "Messenger.h"
#include <cassert>
#include <iostream>

Game::Game(sf::RenderWindow* _RenderWindow)
{
	mActive = true;

	mMessengers.emplace(std::make_pair("KeyEvents", std::make_shared<Messenger>()));
	mMessengers.emplace(std::make_pair("GlobalEvents", std::make_shared<Messenger>()));

	GetMessenger("KeyEvents").get()->AddListener(this);
	GetMessenger("GlobalEvents").get()->AddListener(this);

	mCurrentWorld = std::make_shared<World>(this);

	mRenderWindow = _RenderWindow;

	mClock.restart();

	mLastPhysicsTime	= mClock.getElapsedTime();
	mLastControllerTime = mClock.getElapsedTime();

	mPhysicsThread		= std::thread(&Game::PhysicsThread,		this);
	mControllerThread	= std::thread(&Game::ControllerThread,	this);
	mRenderingThread	= std::thread(&Game::RenderingThread,	this);
	mMessagingThread	= std::thread(&Game::MessagingThread,	this);
}

Game::~Game()
{
	mActive = false;

	while (mPhysicsThreadActive || mRenderingThreadActive || mControllerThreadActive || mMessagingThreadActive)
	{
		std::this_thread::yield();
	}

	if (mPhysicsThread.joinable())
	{
		mPhysicsThread.join();
	}

	if (mControllerThread.joinable())
	{
		mControllerThread.join();
	}

	if (mRenderingThread.joinable())
	{
		mRenderingThread.join();
	}

	if (mMessagingThread.joinable())
	{
		mMessagingThread.join();
	}

	mRenderWindow->close();
}

/// <summary> 
/// Primary thread for ticking physics.
/// </summary>
void Game::PhysicsThread()
{
	mPhysicsThreadActive = true;

	while (mActive && mPhysicsThreadActive)
	{
		// Always wait for rendering to complete -TODO- Double buffer all rendering objects so we can
		// skip this. -TODO- 
		while (mRendering)
		{
			std::this_thread::yield();
		}

		sf::Time CurrentTime = mClock.getElapsedTime();

		// Tick Physics
		mCurrentWorld.get()->Tick(CurrentTime - mLastPhysicsTime);

		mLastPhysicsTime = CurrentTime;

		mRendering = true;
	}

	mPhysicsThreadActive = false;
	mActive = false;
}

/// <summary> 
/// Primary thread for ticking controllers.
/// </summary>
void Game::ControllerThread()
{
	mControllerThreadActive = true;

	while (mActive && mControllerThreadActive)
	{
		CheckControls();

		sf::Time CurrentTime = mClock.getElapsedTime();

		// Tick the controller
		mCurrentWorld.get()->ControllerTick(CurrentTime - mLastControllerTime);

		mLastControllerTime = CurrentTime;
	}

	mControllerThreadActive = false;
	mActive = false;
}

/// <summary> 
/// Primary rendering thread.
/// </summary>
void Game::RenderingThread()
{
	mRenderingThreadActive = true;

	// Pick up the window inactive so no other threads can handle it.
	mRenderWindow->setActive(true);

	while (mActive && mRenderingThreadActive)
	{
		// Always wait for physics to complete at least one pass
		while (!mRendering)
		{
			std::this_thread::yield();
		}

		// Clear screen with black
		mRenderWindow->clear(sf::Color(0,0,0,255));

		// Tick Rendering through world's scene graph
		mCurrentWorld.get()->RenderTick();

		// Throw the buffer to display!
		mRenderWindow->display();

		mRendering = false;
	}

	mRenderingThreadActive = false;
	mActive = false;
}

/// <summary> 
/// Primary Messaging thread.
/// </summary>
void Game::MessagingThread()
{
	mMessagingThreadActive = true;

	while (mActive && mMessagingThreadActive)
	{
		// -TODO- Weigh whether these warrant two independant threads.
		// While the message queue is not empty, give messages to messengers.
		while (mMessageQueue.size() > 0)
		{
			GetMessenger(mMessageQueue.front().first).get()->ReceiveMessage(std::move(mMessageQueue.front().second));
			mMessageQueue.pop();
		}

		// For all messengers, tick.
		for (std::pair<std::string, std::shared_ptr<Messenger>> it : mMessengers)
		{
			it.second->TickMessenger();
		}
	}

	mMessagingThreadActive = false;
	mActive = false;
}

/// <summary> 
/// Interprets messages passed.
/// </summary>
void Game::ReadMessage(Message* _Message)
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
		case MESSAGE_TYPE_QUIT:
			std::cout << _Message->GetMessageString(); // -TODO- Implement a logging file so this can be written to it on exit.
			EndGame(); // Quit
			break;
		default:

			break;
	}
}

/// <summary> 
/// Checks controls, should only be used with overrides, as the global level shouldn't be
/// looking for any specific key inputs.
/// </summary>
void Game::CheckControls(int _OverrideControl)
{
	// -TODO- Implment any GLOBAL controls here.
}

/// <summary> 
/// Returns a pointer to the messenger requested
/// </summary>
std::shared_ptr<Messenger> Game::GetMessenger(std::string _MessengerName)
{
	std::map<std::string, std::shared_ptr<Messenger>>::iterator Result = mMessengers.find(_MessengerName);
	assert(Result != mMessengers.end());
	return mMessengers.find(_MessengerName)->second;
}


void Game::QueueMessage(std::string _MessengerName, std::unique_ptr<Message> _Message)
{
	mMessageQueue.push(std::make_pair(_MessengerName, std::move(_Message)));
}