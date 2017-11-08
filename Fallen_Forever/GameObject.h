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

class GameObject : public Listener, public sf::Transformable
{
public:
	GameObject() { mRenderStates = sf::RenderStates::Default; }
	~GameObject() {}
	void RenderTick(sf::RenderWindow* _RenderWindow);
	void Tick(sf::Time _DeltaTime) {}
	void ControllerTick(sf::Time _DeltaTime) {}
	void SetController(Controller* _Controller) {}
	Controller* GetController() { return mController; }
	void SetTexResources(TextureResources* _ResourceHolder);

protected:
	std::pair<double, double> mPosition;				// The object's position
	std::pair<double, double> mSize;					// The object's size
	std::pair<double, double> mVelocity;				// The object's velocity

	double mRotation;									// The Object's rotation
	double mMass;										// The Object's mass
	double mIntegrity;									// The Object's Hitpoints
	double mHardness;									// The Object's Resistance
	
	bool mPhysical;										// Whether or not the Object can collide.

	int  mLayer;										// The Object's layer (for rendering and physics)

	std::vector<std::shared_ptr<GameObject>> mChildren;	// The Object's children

	sf::Sprite mSprite;									// The Object's image
	sf::RenderStates mRenderStates;						// The Object's RenderStates

	TextureResources* mResourceHolder;					// A pointer to resource holder for object texture

private:
	Controller* mController;
};