#pragma once

class Collidable
{
public:
	virtual void Collide(Collidable* _Collidable) = 0;
	virtual void CheckCollision(Collidable* _Collidable);
	void CreateCollider(double* _XPtr, double* _YPtr, double* _RadiusPtr);
protected:
	double* XPtr;
	double* YPtr;
	double* RadiusPtr;
};