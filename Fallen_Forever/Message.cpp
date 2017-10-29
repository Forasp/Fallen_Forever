#include "Message.h"

Message::Message(int _MessageType, std::string _MessageString, bool _Consumable)
{
	mMessageType = _MessageType;
	mMessageString = _MessageString;
	mConsumable = _Consumable;
	mConsumed = false;
}

Message::Message(int _MessageType, double _MessageDouble, bool _Consumable)
{
	mMessageType = _MessageType;
	mMessageDouble = _MessageDouble;
	mConsumable = _Consumable;
	mConsumed = false;
}

/// <summary> 
/// If the message is consumable, consume it.
/// This prevents the message from being used by any further listeners.
/// </summary>
void Message::Consume()
{
	if (mConsumable)
	{
		mConsumed = true;
	}
}

/// <summary> 
/// Sets whether a message is consumable or not.
/// </summary>
void Message::SetConsumable(bool _Consumable)
{
	mConsumable = _Consumable;
}

/// <summary> 
/// Gets the type of message, returns invalid if consumed.
/// </summary>
int Message::GetMessageType()
{
	if (mConsumed)
	{
		return MESSAGE_TYPE_INVALID;
	}

	return mMessageType;
}

/// <summary> 
/// Gets the string of the message.
/// </summary>
std::string Message::GetMessageString()
{
	return mMessageString;
}

/// <summary> 
/// Gets the message double contents.
/// </summary>
double Message::GetMessageDouble()
{
	return mMessageDouble;
}
