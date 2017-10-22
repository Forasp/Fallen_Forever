#include "Game.h"
#include "World.h"
#include "SFML/Window/Keyboard.hpp"

Game::Game(sf::RenderWindow* _RenderWindow)
{
	mActive = true;

	mCurrentWorld = new World(this);

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
		// Always wait for rendering to complete
		while (mRendering)
		{
			std::this_thread::yield();
		}

		sf::Time CurrentTime = mClock.getElapsedTime();

		// Tick Physics
		mCurrentWorld->Tick(CurrentTime - mLastPhysicsTime);

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
		mCurrentWorld->ControllerTick(CurrentTime - mLastControllerTime);

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
		// Always wait for rendering to complete
		while (!mRendering)
		{
			std::this_thread::yield();
		}

		// Tick Rendering
		mRenderWindow->clear();
		mCurrentWorld->RenderTick();
		mRenderWindow->display();

		mRendering = false;
	}

	mRenderingThreadActive = false;
	mActive = false;
}

void Game::CheckControls()
{
	if (mActive && sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mActive = false;
	}
}