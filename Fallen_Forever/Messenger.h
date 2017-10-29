#pragma once
#include "Listener.h"
#include "Message.h"
#include <vector>

class Messenger
{
public:
	virtual void AddListener(Listener* _Listener);
	virtual void RemoveListener(Listener* _Listener);
	virtual void ReceiveMessage(Message _Message); // -TODO- convert all messages to unique pointers to kill all overhead
private:
	std::vector<Listener*> mListeners;
};