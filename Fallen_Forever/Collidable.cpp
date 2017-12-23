#include "Collidable.h"
#include "Message.h"
#include <math.h>
#include "GameObject.h"

void Collidable::CheckCollision(Collidable* _Collidable)
{
	if (mSizePtr == nullptr || mPositionPtr == nullptr || _Collidable->mSizePtr == nullptr || _Collidable->mPositionPtr == nullptr || _Collidable == this)
	{
		return;
	}

 	double ThisRadius = RadiusFromSize(mSizePtr);
	double OtherRadius = RadiusFromSize(_Collidable->mSizePtr);

	// If distance is greater than the two radii, then there can be no collision.
	if (DistanceBetweenPoints(mPositionPtr, _Collidable->mPositionPtr) > ThisRadius + OtherRadius)
	{
		return;
	}

	// Move on to pixel perfect collision.
	std::pair<int, int> FoundCoordinates1 = std::make_pair(int(0), int(0));
	std::pair<int, int> FoundCoordinates2 = std::make_pair(int(0), int(0));
	int CoordinateScale = 2;
	bool Collided = true;

	while (CoordinateScale <= 32 && Collided)
	{
		Collided = false;

		for (int x = 0; x < 2; x++)
		{
			for (int y = 0; y < 2; y++)
			{
				if (Collided)
				{
					continue;
				}

				bool Collidable = false;

				switch (CoordinateScale)
				{
					case 2:
						Collidable = mCollisionAreaXL[x + FoundCoordinates1.first][y + FoundCoordinates1.second];
						break;
					case 4:
						Collidable = mCollisionAreaL[x + FoundCoordinates1.first][y + FoundCoordinates1.second];
						break;
					case 8:
						Collidable = mCollisionAreaM[x + FoundCoordinates1.first][y + FoundCoordinates1.second];
						break;
					case 16:
						Collidable = mCollisionAreaS[x + FoundCoordinates1.first][y + FoundCoordinates1.second];
						break;
					case 32:
						Collidable = mCollisionAreaXS[x + FoundCoordinates1.first][y + FoundCoordinates1.second];
						break;
				}

				if (Collidable)
				{
					// vector between center of block and center of image
					std::pair<double, double> TempVector = std::make_pair(double((((x + FoundCoordinates1.first) / double(CoordinateScale - 1)) - 0.5f) * mSizePtr->first),
																		  double((((y + FoundCoordinates1.second) / double(CoordinateScale - 1)) - 0.5f) * mSizePtr->second));
					// Rotate vector
					std::pair<double, double> RotatedVector = RotateVector(&TempVector, *mRotationPtr);

					// Update position to global
					RotatedVector.first += mPositionPtr->first;
					RotatedVector.second += mPositionPtr->second;

					// Check Distance Against other item's pixels
					for (int x2 = 0; x2 < 2; x2++)
					{
						for (int y2 = 0; y2 < 2; y2++)
						{
							if (Collided)
							{
								continue;
							}

							bool Collidable2 = false;

							switch (CoordinateScale)
							{
								case 2:
									Collidable2 = _Collidable->mCollisionAreaXL[x2 + FoundCoordinates2.first][y2 + FoundCoordinates2.second];
									break;
								case 4:
									Collidable2 = _Collidable->mCollisionAreaL[x2 + FoundCoordinates2.first][y2 + FoundCoordinates2.second];
									break;
								case 8:
									Collidable2 = _Collidable->mCollisionAreaM[x2 + FoundCoordinates2.first][y2 + FoundCoordinates2.second];
									break;
								case 16:
									Collidable2 = _Collidable->mCollisionAreaS[x2 + FoundCoordinates2.first][y2 + FoundCoordinates2.second];
									break;
								case 32:
									Collidable2 = _Collidable->mCollisionAreaXS[x2 + FoundCoordinates2.first][y2 + FoundCoordinates2.second];
									break;
							}

							if (Collidable2)
							{
								// vector between center of block and center of image
								std::pair<double, double> TempVector2 = std::make_pair(double((((x2 + FoundCoordinates2.first) / double(CoordinateScale - 1)) - 0.5) * _Collidable->mSizePtr->first),
																					   double((((y2 + FoundCoordinates2.second) / double(CoordinateScale - 1)) - 0.5) * _Collidable->mSizePtr->second));
								// Rotate vector
								std::pair<double, double> RotatedVector2 = RotateVector(&TempVector2, *_Collidable->mRotationPtr);

								// Update position to global
								RotatedVector2.first += _Collidable->mPositionPtr->first;
								RotatedVector2.second += _Collidable->mPositionPtr->second;

								if (DistanceBetweenPoints(&RotatedVector, &RotatedVector2) * 1.25 < (ThisRadius / 2 / double(CoordinateScale)) + (OtherRadius / 2 / double(CoordinateScale)))
								{
									Collided = true;
									FoundCoordinates1 = std::make_pair(x * 2 + (FoundCoordinates1.first * 2), y * 2 + (FoundCoordinates1.second * 2));
									FoundCoordinates2 = std::make_pair(x2 * 2 + (FoundCoordinates2.first * 2), y2 * 2 + (FoundCoordinates2.second * 2));
								}
							}
						}
					}
				}
			}
		}

		CoordinateScale *= 2;
	}

 	if (Collided)
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

void Collidable::PopulateCollisionAreas(sf::Sprite* _Sprite)
{
	sf::Image TempImage;
	TempImage = _Sprite->getTexture()->copyToImage();

	for (unsigned int x = 0; x < TempImage.getSize().x; x++)
	{
		for (unsigned int y = 0; y < TempImage.getSize().y; y++)
		{
			unsigned int ImageWidth = TempImage.getSize().x;
			unsigned int ImageHeight = TempImage.getSize().y;

			bool PixelCollidable = bool(TempImage.getPixel(x, y).a == 0u);

			mCollisionAreaXS[x / (ImageWidth / 32)][y / (ImageHeight / 32)] |= PixelCollidable;
			mCollisionAreaS[ x / (ImageWidth / 16)][y / (ImageHeight / 16)] |= PixelCollidable;
			mCollisionAreaM[ x / (ImageWidth / 8)][ y / (ImageHeight / 8)]  |= PixelCollidable;
			mCollisionAreaL[ x / (ImageWidth / 4)][ y / (ImageHeight / 4)]  |= PixelCollidable;
			mCollisionAreaXL[x / (ImageWidth / 2)][ y / (ImageHeight / 2)]  |= PixelCollidable;
		}

	}
}
