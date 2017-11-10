#pragma once
#include "Listener.h"

class GameObject;

class Controller : public Listener
{
public:
	Controller(GameObject* _Parent) { mParent = _Parent; }
	~Controller() {};

	void SetParent(GameObject* _Parent) { mParent = _Parent; }
	void ControllerTick() {};

protected:
	GameObject* mParent;

};