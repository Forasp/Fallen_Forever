#include "Messenger.h"

/// <summary> 
/// Adds a listener to the Messenger. 
/// </summary>
void Messenger::AddListener(Listener* _Listener)
{
	mListeners.push_back(_Listener);
}

/// <summary> 
/// Remove a listener from the Messenger 
/// </summary>
void Messenger::RemoveListener(Listener* _Listener)
{
	unsigned int ListenerIndex = 0;
	bool ListenerFound = false;

	for (unsigned int i = 0; i < mListeners.size(); i++)
	{
		if (mListeners[i] == _Listener)
		{
			ListenerIndex = i;
			ListenerFound = true;
			break;
		}
	}

	if (ListenerFound)
	{
		mListeners.erase(mListeners.begin() + ListenerIndex);
	}
}

/// <summary> 
/// Receive a message and distribute to all listeners.
/// </summary>
void Messenger::ReceiveMessage(Message _Message)
{
	for (Listener* i : mListeners)
	{
		i->ReadMessage(&_Message);
	}
}