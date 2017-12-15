#pragma once
#include <utility>
#include "Listener.h"

class Message;

class Collidable : public virtual Listener
{
public:
	Collidable() {
		mPositionPtr = nullptr;
		mSizePtr = nullptr;
		mRotationPtr = nullptr;
	}
	virtual void Collide(Collidable* _Collidable) = 0;
	virtual void CheckCollision(Collidable* _Collidable);
	void CreateCollider(std::pair<double, double>* _PositionPtr, std::pair<double, double>* _SizePtr, double* _RotationPtr);
	void CollisionTick();
	void ReadMessage(Message* _Message);
	virtual void CollisionBroadcast() = 0;


	std::pair<double, double>* mPositionPtr;
	std::pair<double, double>* mSizePtr;
	double* mRotationPtr;
	std::pair<double, double> mPastPosition;
	std::pair<double, double> mPastSize;
	double mPastRotation;

};