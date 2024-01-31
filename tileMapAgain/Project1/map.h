#pragma once
#include "tools.h"

#define MAP_WIDTH 10
#define MAP_HEIGHT 10
#define BLOCK_SIZE 64.f

typedef struct BlocksTileMap {
	int id;
	sfVector2f pos;
	sfVector2f scale;
	sfVector2i iPos;
	sfIntRect rect;
	sfBool collide;
}BlocksTileMap;
BlocksTileMap block[MAP_HEIGHT][MAP_WIDTH];

void initMap();
void updateMap();
void displayMap(sfRenderTexture* _texture);
//sfBool collisionMapPlayer(sfFloatRect _sprite, int _direction, sfVector2f _vitesse);