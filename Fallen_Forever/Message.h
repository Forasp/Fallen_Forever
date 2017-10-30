#pragma once
#include <string>

#define MESSAGE_TYPE_INVALID -1
#define MESSAGE_TYPE_STRING 1
#define MESSAGE_TYPE_DOUBLE 2
#define MESSAGE_TYPE_INPUT  3
#define MESSAGE_TYPE_QUIT   4

class Message
{
public:
	Message(int _MessageType, std::string _MessageString, bool _Consumable = false);
	Message(int _MessageType, double _MessageDouble, bool _Consumable = false);

	void Consume();
	void SetConsumable(bool _Consumable);
	int GetMessageType();
	std::string GetMessageString();
	double GetMessageDouble();

private:
	bool mConsumed;
	bool mConsumable;

	int mMessageType;

	std::string mMessageString;

	double mMessageDouble;
};