#pragma once

class Contrller;

class GameObject
{
public:
	GameObject() {}
	~GameObject() {}
	void RenderTick() {}
	void Tick(sf::Time _DeltaTime) {}
	void ControllerTick(sf::Time _DeltaTime) {}
	void SetController(Controller* _Controller) {}
	Controller* GetController() { return mController; }
private:

	Controller* mController;
};