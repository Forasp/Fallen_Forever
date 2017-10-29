#include "Game.h"
#include "World.h"
#include "SFML/Window/Keyboard.hpp"
#include "Message.h"

Game::Game(sf::RenderWindow* _RenderWindow)
{
	mActive = true;

	mCurrentWorld = std::make_shared<World>(this);

	mRenderWindow = _RenderWindow;

	mClock.restart();

	mLastPhysicsTime	= mClock.getElapsedTime();
	mLastControllerTime = mClock.getElapsedTime();

	mPhysicsThread		= std::thread(&Game::PhysicsThread, this);
	mControllerThread	= std::thread(&Game::ControllerThread, this);
	mRenderingThread	= std::thread(&Game::RenderingThread, this);
}

Game::~Game()
{
	mActive = false;

	while (mPhysicsThreadActive || mRenderingThreadActive || mControllerThreadActive)
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

	mRenderWindow->close();
}


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

void Game::RenderingThread()
{
	mRenderingThreadActive = true;

	while (mActive && mRenderingThreadActive)
	{
		// Always wait for physics to complete at least one pass
		while (!mRendering)
		{
			std::this_thread::yield();
		}

		// Tick Rendering
		mRenderWindow->clear();
		mCurrentWorld.get()->RenderTick();
		mRenderWindow->display();

		mRendering = false;
	}

	mRenderingThreadActive = false;
	mActive = false;
}

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
		default:

			break;
	}
}

void Game::CheckControls(int _OverrideControl)
{
	// -TODO- Implment GLOBAL controls.
	//if (mActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	if (mActive && _OverrideControl == sf::Keyboard::Escape)
	{
		mActive = false;
	}
}