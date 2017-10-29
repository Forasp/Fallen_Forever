#pragma once

class Message;

class Listener
{
public:
	virtual void ReadMessage(Message* _Message) {};
};