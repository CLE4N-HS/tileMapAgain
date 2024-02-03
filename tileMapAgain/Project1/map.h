#pragma once
#include "tools.h"
#include "math.h"

#define BLOCK_SIZE 64.f
//#define MAP_WIDTH_IN_PIXELS 1920
//#define MAP_HEIGHT_IN_PIXELS 1080

typedef struct BlocksTileMap {
	int id;
	sfVector2f pos;
	sfVector2f scale;
	sfVector2i iPos;
	sfIntRect rect;
	sfBool isSolid;
	int layer;
	sfBool canGoUnder;
}BlocksTileMap;
BlocksTileMap** block;
//BlocksTileMap block[MAP_HEIGHT][MAP_WIDTH];

int mapWidth;
int mapHeight;

void initMap();
void updateMap();
void displayMap(sfRenderTexture* _texture);
sfBool isBlockSolid(sfVector2i _block);
//sfBool collisionMapPlayer(sfFloatRect _sprite, int _direction, sfVector2f _vitesse);