#include "Collidable.h"
#include <math.h>

void Collidable::CheckCollision(Collidable* _Collidable)
{
	if ((fabs(*_Collidable->XPtr - *XPtr) + fabs(*_Collidable->YPtr - *YPtr)) < (*_Collidable->RadiusPtr + *RadiusPtr))
	{
		Collide(_Collidable);
	}
}

void Collidable::CreateCollider(double* _XPtr, double* _YPtr, double* _RadiusPtr)
{
	XPtr = _XPtr;
	YPtr = _YPtr;
	RadiusPtr = _RadiusPtr;
}