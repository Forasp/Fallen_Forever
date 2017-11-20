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
	// Empty constructors/destructors
	Message() {};
	~Message() {};

	// Constructor with only message type
	Message(int _MessageType, bool _Consumable = false) : mMessageType(_MessageType), mConsumable(_Consumable), mConsumed(false) {}

	// Constructors with message type and  a single parameter
	Message(int _MessageType, int _MessageInt, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// Constructors with message type and two parameters
	Message(int _MessageType, int _MessageInt, double _MessageDouble, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, int _MessageInt, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, int _MessageInt, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, std::pair<double, double> _MessageDoublePair, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDoublePair(_MessageDoublePair), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// Constructors with message type and three parameters
	Message(int _MessageType, int _MessageInt, double _MessageDouble, std::pair<double, double> _MessageDoublePair, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, int _MessageInt, double _MessageDouble, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}
	Message(int _MessageType, double _MessageDouble, std::pair<double, double> _MessageDoublePair, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}

	// Constructor with all parameters
	Message(int _MessageType, int _MessageInt, double _MessageDouble, std::pair<double, double> _MessageDoublePair, std::string _MessageString, bool _Consumable = false) :
		mMessageType(_MessageType), mMessageInt(_MessageInt), mMessageDouble(_MessageDouble), mMessageDoublePair(_MessageDoublePair), mMessageString(_MessageString), mConsumable(_Consumable), mConsumed(false) {}


	void Consume()
	{
		if (mConsumable)
		{
			mConsumed = true;
		}
	}

	void SetConsumable(bool _Consumable)
	{
		mConsumable = _Consumable;
	}

	int GetMessageType() { return mMessageType; }
	int GetMessageInt() { return mMessageInt; }
	double GetMessageDouble() { return mMessageDouble; }
	std::pair<double, double> GetMessageDoublePair() { return mMessageDoublePair; }
	std::string GetMessageString() { return mMessageString; }

protected:
	bool mConsumed;
	bool mConsumable;

	int mMessageType;
	int mMessageInt;
	double mMessageDouble;
	std::pair<double, double> mMessageDoublePair;
	std::string mMessageString;
};