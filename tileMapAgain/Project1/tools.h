#pragma once
#include "SFML/Graphics.h"
#include "SFML/Window.h"
#include "SFML/Audio.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "player.h"
#include "view.h"
#include "map.h"


#define WINDOW_LENGTH 1920
#define WINDOW_HEIGHT 1080
#define EPSILON (float)1e-6
#define DEG2RAD 0.0174533
#define RAD2DEG 57.295779
#define PI 3.141593
#define LERP(a,b,t) (b-a)t+a

#define TEXTURE_PATH "../Ressources/Textures/"
#define AUDIO_PATH "../Ressources/SoundsFX/"
#define FROG_PATH TEXTURE_PATH "Player/Ninja Frog/"
#define VIRTUALGUY_PATH TEXTURE_PATH "Player/Virtual Guy/"


sfTime sftime;
sfClock* sfclock;

sfVector2f vector2f(float _x, float _y);
sfVector2i vector2i(int _x, int _y);
int iRand(int _min, int _max);
void initTools();
void restartClock();
float getDeltaTime();

//sfVector2f LerpVector(sfVector2f _a, sfVector2f _b, float _t);
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

float Lerp(float _a, float _b, float _t);

sfBool Equals(sfVector2f _v1, sfVector2f _v2);

//sfBool PlayerCanSeeEnemy(sfVector2f _pPos, sfVector2f _ePos, sfVector2f _POVPos, float _FOV, float _pAngle);

sfBool IsInFOV(sfVector2f _lookingObject, sfVector2f _forwardVector, sfVector2f _targetObject, float _maxRadius, float _fieldOfView);