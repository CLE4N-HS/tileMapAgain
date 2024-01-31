#include "tools.h"

sfVector2f vector2f(float _x, float _y)
{
    sfVector2f v = { _x, _y };
    return v;
}

int iRand(int _min, int _max)
{
    return rand() % (_max - _min + 1) + _min;
}

void initTools()
{
    sfclock = sfClock_create();
    srand(time(NULL));
}

void restartClock()
{
    sftime = sfClock_restart(sfclock);
}

float getDeltaTime()
{
    if (sfTime_asSeconds(sftime) > 1.0f) return 1.0f;
    return sfTime_asSeconds(sftime);
}

//sfVector2f LerpVector(sfVector2f _a, sfVector2f _b, float _t)
//{
//    return vector2f(LERP(_a.x, _b.x, _t), LERP(_a.y, _b.y, _t));
//}

/// <summary>
/// Give the Polar Coordinates with a base and a target
/// </summary>
/// <param name="v">The base position</param>
/// <param name="r">The distance compared to the base (use GetMagnitude() if you need a distance)</param>
/// <param name="theta">The angle in Radiant (use DEG2RAG if needed), 0 is on the right, clockwise, PI/2 is on the bottom</param>
/// <returns>Carthésian coordinates of the target</returns>
sfVector2f PolarCoords(sfVector2f v, float r, float theta)
{
    return vector2f(v.x + (r * cosf(theta)), v.y + (r * sinf(theta)));
}

/// <summary>
/// Create a vector using 2 other vectors
/// </summary>
/// <param name="_pos1">Start point</param>
/// <param name="_pos2">End point</param>
/// <returns>1 third vector2f</returns>
sfVector2f CreateVector(sfVector2f _v1, sfVector2f _v2)
{
    sfVector2f v = { (_v2.x - _v1.x) , (_v2.y - _v1.y) };
    return v;
}

/// <summary>
/// Add two vectors together
/// </summary>
/// <param name="_v1"></param>
/// <param name="_v2"></param>
/// <returns>1 third vector2f</returns>
sfVector2f AddVectors(sfVector2f _v1, sfVector2f _v2)
{
    sfVector2f v = { _v1.x + _v2.x, _v1.y + _v2.y };
    return v;
}

/// <summary>
/// Substract two vectors -> the First minus Second vector
/// </summary>
/// <param name="_v1">The first number</param>
/// <param name="_v2">The second number</param>
/// <returns>A third vector2f</returns>
sfVector2f SubstractVectors(sfVector2f _v1, sfVector2f _v2)
{
    sfVector2f v = { _v1.x - _v2.x, _v1.y - _v2.y };
    return v;
}

/// <summary>
/// Dot Product of two Vectors
/// </summary>
/// <param name="_v1">First vector</param>
/// <param name="_v2">Second vector</param>
/// <returns>Dot Product in float between -1 and 1</returns>
float DotProduct(sfVector2f _v1, sfVector2f _v2)
{
    float d = (_v1.x * _v2.x + _v1.y * _v2.y);
    return d;
}

/// <summary>
/// Magnitude of a vector using sqrtf
/// </summary>
/// <param name="_vector">A Vector</param>
/// <returns>Magnitude (distance) in float</returns>
float GetMagnitude(sfVector2f _vector)
{
    float m = sqrtf(_vector.x * _vector.x + _vector.y * _vector.y);
    return m;
}

/// <summary>
/// Normalize a Vector
/// </summary>
/// <param name="_vector">A vector</param>
/// <returns>A vector between {-1,-1} and {1,1}</returns>
sfVector2f Normalize(sfVector2f _vector)
{
    float magnitude = GetMagnitude(_vector);
    if (magnitude < EPSILON) return _vector;
    sfVector2f v = { _vector.x / magnitude, _vector.y / magnitude };
    return v;
}

/// <summary>
/// Magnitude of a vector without using sqrtf
/// </summary>
/// <param name="_vector">A Vector</param>
/// <returns>Square of Magnitude (distance) in float</returns>
float GetSqrMagnitude(sfVector2f _vector)
{
    float m = (_vector.x * _vector.x + _vector.y * _vector.y);
    return m;
}

/// <summary>
/// Multiply a vector by a multiplier
/// </summary>
/// <param name="_vector">A vector</param>
/// <param name="_multiply">The multiplier</param>
/// <returns>The Vector muliplied by the float</returns>
sfVector2f MultiplyVector(sfVector2f _vector, float _multiplier)
{
    sfVector2f v = { _vector.x * _multiplier, _vector.y * _multiplier };
    return v;
}

/// <summary>
/// Get the angle between two vectors
/// </summary>
/// <param name="_v1">First vector</param>
/// <param name="_v2">Second vector</param>
/// <returns>The angle in degrees</returns>
float GetAngleBetweenVectors(sfVector2f _v1, sfVector2f _v2)
{
    float a = atan2f(_v2.y, _v2.x) - atan2f(_v1.y, _v1.x);
    return a;
}

float Lerp(float _a, float _b, float _t)
{
    return (_b - _a) * _t + _a;
}

sfBool Equals(sfVector2f _v1, sfVector2f _v2)
{
    float xOffset = _v2.x - _v1.x;
    float yOffset = _v2.y - _v1.y;

    if (fabs(xOffset) < EPSILON && fabs(yOffset) < EPSILON)
    {
        return sfTrue;
    }
    return sfFalse;
}

/// <summary>
/// Check if a lookingObject can see the targetedObject with a max distance and an FOV
/// </summary>
/// <param name="_lookingObject">The looking object</param>
/// <param name="_forwardVector">The forward vector of the looking object</param>
/// <param name="_targetObject">The targeted object</param>
/// <param name="_maxRadius">The maximum distance visible</param>
/// <param name="_fieldOfView">The FOV of the looking object</param>
/// <returns>If the targeted object is in the FOV of the looking object</returns>
sfBool IsInFOV(sfVector2f _lookingObject, sfVector2f _forwardVector, sfVector2f _targetObject, float _maxRadius, float _fieldOfView)
{
    sfVector2f lookToTargetVector = CreateVector(_lookingObject, _targetObject);
    float sqrdistance = GetSqrMagnitude(lookToTargetVector);
    if (sqrdistance > _maxRadius * _maxRadius) return sfFalse;

    sfVector2f lookToTargetNorm = Normalize(lookToTargetVector);
    if (DotProduct(lookToTargetNorm, _forwardVector) > cosf(_fieldOfView * DEG2RAD * 0.5f)) return sfTrue;

    return sfFalse;

}


//sfBool PlayerCanSeeEnemy(sfVector2f _pPos, sfVector2f _ePos, sfVector2f _POVPos, float _FOV, float _pAngle)
//{
//    sfVector2f playerToEnemy;
//    playerToEnemy = CreateVector(vector2f(_pPos.x, _pPos.y), vector2f(_ePos.x, _ePos.y));
//    sfVector2f playerToFOV;
//    playerToFOV = CreateVector(vector2f(_pPos.x, _pPos.y), vector2f(_POVPos.x, _POVPos.y));
//    
//    float playerToEnemyMagnitude;
//    playerToEnemyMagnitude = GetMagnitude(playerToEnemy);
//    float playerToFOVMagnitude;
//    playerToFOVMagnitude = GetMagnitude(playerToFOV);
//
//    sfVector2f playerToEnemyNormalize;
//    playerToEnemyNormalize = Normalize(playerToEnemy);
//    sfVector2f playerToFOVNormalize;
//    playerToFOVNormalize = Normalize(playerToFOV);
//
//    float dotProduct;
//    dotProduct = DotProduct(playerToEnemyNormalize, playerToFOVNormalize);
//   // printf("%f\n", dotProduct);
//
//    return sfFalse;
//}