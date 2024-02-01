#pragma once
#include "tools.h"

sfVector2f vector2f(float _x, float _y);
sfVector2i vector2i(int _x, int _y);

float Lerp(float _a, float _b, float _t);
sfVector2f LerpVector(sfVector2f _a, sfVector2f _b, float _t);
sfVector2f PolarCoords(sfVector2f v, float r, float theta);

sfVector2f CreateVector(sfVector2f _v1, sfVector2f _v2);
sfVector2f AddVectors(sfVector2f _v1, sfVector2f _v2);
sfVector2f SubstractVectors(sfVector2f _v1, sfVector2f _v2);
float DotProduct(sfVector2f _v1, sfVector2f _v2);
float GetMagnitude(sfVector2f _vector);
sfVector2f Normalize(sfVector2f _vector);
float GetSqrMagnitude(sfVector2f _vector);
sfVector2f MultiplyVector(sfVector2f _vector, float _multiply);
float GetAngleBetweenVectors(sfVector2f _v1, sfVector2f _v2);

sfBool Equals(sfVector2f _v1, sfVector2f _v2);

//sfBool PlayerCanSeeEnemy(sfVector2f _pPos, sfVector2f _ePos, sfVector2f _POVPos, float _FOV, float _pAngle);

sfBool IsInFOV(sfVector2f _lookingObject, sfVector2f _forwardVector, sfVector2f _targetObject, float _maxRadius, float _fieldOfView);