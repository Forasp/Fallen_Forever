#pragma once

class GameObject;

class Controller
{
public:
	Controller(GameObject* _Parent) { mParent = _Parent; }
	~Controller() {};

	void SetParent(GameObject* _Parent) { mParent = _Parent; }
	void ControllerTick() {};

private:
	GameObject* mParent;

};