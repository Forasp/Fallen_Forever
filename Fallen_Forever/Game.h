#pragma once
#include <thread>
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics.hpp"
#include <memory>
#include "Listener.h"
#include <map>
#include <queue>

class World;
class Messenger;
class Message;

class Game : public Listener
{
public:
	Game(sf::RenderWindow* _RenderWindow, bool _CoupleRenderingToPhysics = false);
	~Game();

	void PhysicsThread();
	void ControllerThread();
	void RenderingThread();
	void MessagingThread();

	void EndGame() { mActive = false; }

	std::shared_ptr<Messenger> GetMessenger(std::string _MessengerName);

	void QueueMessage(std::string _MessengerName, std::unique_ptr<Message> _Message);

	bool IsActive() { return (mActive || mPhysicsThreadActive || mRenderingThreadActive || mControllerThreadActive); }

	virtual void ReadMessage(Message* _Message);

private:
	std::shared_ptr<World> mCurrentWorld;
	std::map<std::string, std::shared_ptr<Messenger>> mMessengers;
	std::queue<std::pair<std::string, std::unique_ptr<Message>>> mMessageQueue;

	sf::RenderWindow* mRenderWindow;

	sf::Clock mClock;

	std::thread mPhysicsThread;
	std::thread mControllerThread;
	std::thread mRenderingThread;
	std::thread mMessagingThread;

	bool mRendering;
	bool mActive;
	bool mPhysicsThreadActive;
	bool mRenderingThreadActive;
	bool mControllerThreadActive;
	bool mMessagingThreadActive;
	bool mCoupleRenderingToPhysics;

	sf::Time mLastPhysicsTime;
	sf::Time mLastControllerTime;
	sf::Time mLastRenderTime;
	sf::Time mLastMessagingTime;

	virtual void CheckControls(int _OverrideControl = -1);
};