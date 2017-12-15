#include "Collidable.h"
#include "Message.h"
#include <math.h>
#include "GameObject.h"

void Collidable::CheckCollision(Collidable* _Collidable)
{
	if (mSizePtr == nullptr || mPositionPtr == nullptr || _Collidable->mSizePtr == nullptr || _Collidable->mPositionPtr == nullptr)
	{
		return;
	}

	// -TODO- Update to handle rotation.
	if ((fabs(_Collidable->mPositionPtr->first - mPositionPtr->first)  < _Collidable->mSizePtr->first + mSizePtr->first) &&
		(fabs(_Collidable->mPositionPtr->second - mPositionPtr->second) < _Collidable->mSizePtr->second + mSizePtr->second))
	{
		_Collidable->Collide(this);

		// Collide can be implemented to delete pointers, always check again.
		Collide(_Collidable != nullptr ? _Collidable : nullptr);
	}
}

void Collidable::CreateCollider(std::pair<double, double>* _PositionPtr, std::pair<double, double>* _SizePtr, double* _RotationPtr)
{
	mPositionPtr = _PositionPtr;
	mSizePtr = _SizePtr;
	mRotationPtr = _RotationPtr;
}

void Collidable::CollisionTick()
{
	if (mPastPosition.first != mPositionPtr->first ||
		mPastPosition.second != mPositionPtr->second ||
		mPastSize.first != mSizePtr->first ||
		mPastSize.second != mSizePtr->second ||
		mPastRotation != *mRotationPtr)
	{
		CollisionBroadcast();
		mPastPosition = *mPositionPtr;
		mPastSize = *mSizePtr;
		mPastRotation = *mRotationPtr;
	}
}

void Collidable::ReadMessage(Message* _Message)
{
	if (_Message->GetMessageType() == MESSAGE_TYPE_EVENT && _Message->GetMessageDouble() == TICK_EVENT)
	{
		CollisionTick();
	}
	else if (_Message->GetMessageType() == MESSAGE_TYPE_COLLISION_PTR)
	{
		Collidable* CollidablePtr = dynamic_cast<Collidable*>(static_cast<GameObject*>(_Message->GetMessageVoidPtr()));
		CheckCollision(CollidablePtr);
	}
}
