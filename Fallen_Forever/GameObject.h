#pragma once
#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Transformable.hpp"
#include "SFML/System/Time.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Listener.h"
#include <memory>
#include "Resources.h"

class Controller;
class Game;

class GameObject : public Listener, public sf::Transformable
{
public:
	GameObject() { mRenderStates = sf::RenderStates::Default; mAddedToRenderer = false; }
	~GameObject();
	virtual void RenderTick(sf::RenderWindow* _RenderWindow);
	virtual void Tick(sf::Time _DeltaTime);
	virtual void ControllerTick(sf::Time _DeltaTime) {}
	virtual void SetController(Controller* _Controller) {}
	virtual Controller* GetController() { return mController; }
	virtual void SetTexResources(TextureResources* _ResourceHolder);
	virtual std::pair<double, double> GetPosition() { return mPosition; }
	virtual std::pair<double, double> GetVelocity() { return mVelocity; }
	virtual std::pair<double, double> GetSize() { return mSize; }

protected:
	std::pair<double, double> mPosition;				// The object's position
	std::pair<double, double> mSize;					// The object's size
	std::pair<double, double> mVelocity;				// The object's velocity

	double mRotation;									// The Object's rotation
	double mMass;										// The Object's mass
	double mIntegrity;									// The Object's Hitpoints
	double mHardness;									// The Object's Resistance
	
	bool mPhysical;										// Whether or not the Object can collide.
	bool mAddedToRenderer;								// Whether or not the object has been handed to the renderer yet.

	int  mLayer;										// The Object's layer (for rendering and physics)

	std::vector<std::shared_ptr<GameObject>> mChildren;	// The Object's children

	sf::Sprite mSprite;									// The Object's image
	sf::RenderStates mRenderStates;						// The Object's RenderStates

	TextureResources* mResourceHolder;					// A pointer to resource holder for object texture

	Game* mGame;										// A Pointer to the Game.

protected:
	Controller* mController;
};