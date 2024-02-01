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
#define TILES_PATH TEXTURE_PATH "Tiles/"
#define AUDIO_PATH "../Ressources/SoundsFX/"
#define FROG_PATH TEXTURE_PATH "Player/Ninja Frog/"
#define VIRTUALGUY_PATH TEXTURE_PATH "Player/Virtual Guy/"


sfTime sftime;
sfClock* sfclock;

int iRand(int _min, int _max);
void initTools();
void restartClock();
float getDeltaTime();