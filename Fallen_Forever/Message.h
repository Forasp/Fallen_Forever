#pragma once
#include <string>

#define MESSAGE_TYPE_INVALID -1
#define MESSAGE_TYPE_STRING 1
#define MESSAGE_TYPE_DOUBLE 2
#define MESSAGE_TYPE_INPUT  3
#define MESSAGE_TYPE_QUIT   4

#define COLLISION_WITH_SELF 1
#define RESTART_LEVEL 2

class Message
{
public:
	Message(int _MessageType, std::string _MessageString, bool _Consumable = false);
	Message(int _MessageType, double _MessageDouble, bool _Consumable = false);
	~Message() {}

	void Consume();
	void SetConsumable(bool _Consumable);
	int GetMessageType();
	std::string GetMessageString();
	double GetMessageDouble();

protected:
	bool mConsumed;
	bool mConsumable;

	int mMessageType;

	std::string mMessageString;

	double mMessageDouble;
};