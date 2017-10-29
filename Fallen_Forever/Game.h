#pragma once
#include <thread>
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Listener.h"

class World;

class Game : public Listener
{
public:
	Game(sf::RenderWindow* _RenderWindow);
	~Game();

	void PhysicsThread();
	void ControllerThread();
	void RenderingThread();

	bool IsActive() { return (mActive || mPhysicsThreadActive || mRenderingThreadActive || mControllerThreadActive); }

	virtual void ReadMessage(Message* _Message);

private:
	std::shared_ptr<World> mCurrentWorld;

	sf::RenderWindow* mRenderWindow;

	sf::Clock mClock;

	std::thread mPhysicsThread;
	std::thread mControllerThread;
	std::thread mRenderingThread;

	bool mRendering;
	bool mActive;
	bool mPhysicsThreadActive;
	bool mRenderingThreadActive;
	bool mControllerThreadActive;

	sf::Time mLastPhysicsTime;
	sf::Time mLastControllerTime;

	virtual void CheckControls(int _OverrideControl = -1);
};