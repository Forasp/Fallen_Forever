#pragma once
#include "Listener.h"

class Contrller;

class GameObject : public Listener
{
public:
	GameObject() {}
	~GameObject() {}
	void RenderTick() {}
	void Tick(sf::Time _DeltaTime) {}
	void ControllerTick(sf::Time _DeltaTime) {}
	void SetController(Controller* _Controller) {}
	Controller* GetController() { return mController; }

protected:
	std::pair<double, double> mPosition;	// The object's position
	std::pair<double, double> mSize;		// The object's size
	std::pair<double, double> mVelocity;	// The object's velocity

	double mRotation;						// The Object's rotation
	double mMass;							// The Object's mass
	double mIntegrity;						// The Object's Hitpoints
	double mHardness;						// The Object's Resistance
	
	bool mPhysical;							// Whether or not the Object can collide.

	int  mLayer;							// The Object's layer (for rendering and physics)

private:

	Controller* mController;
};