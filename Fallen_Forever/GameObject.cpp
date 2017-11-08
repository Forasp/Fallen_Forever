#include "GameObject.h"

void GameObject::RenderTick(sf::RenderWindow* _RenderWindow)
{
	mRenderStates.transform = getTransform();
	_RenderWindow->draw(mSprite, mRenderStates);
}

void GameObject::SetTexResources(TextureResources* _ResourceHolder)
{
	mResourceHolder = _ResourceHolder;
}