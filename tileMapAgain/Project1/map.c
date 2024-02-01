#include "map.h"

char map[10][10] = { {25,18,18,18,18,18,18,18,18,27},
									{11,39,10,10,10,10,10,10,40,9},
									{11,10,10,10,10,10,10,37,38,9},
									{11,10,10,10,10,10,10,10,10,9},
									{11,36,37,37,10,10,10,6,16,9},
									{41,2,2,2,2,2,2,2,2,43},
									{9,9,9,9,9,9,9,9,9,9},
									{9,9,9,9,9,9,9,9,9,9},
									{9,9,9,9,9,9,9,9,9,9},
									{9,9,9,9,9,9,9,9,9,9} };

sfSprite* tile;
sfTexture* tileTexture;
sfRectangleShape* bgRectangle;

void initMap()
{
	tile = sfSprite_create();
	tileTexture = sfTexture_createFromFile(TILES_PATH"CastleTiles.png", NULL);
	sfSprite_setTexture(tile, tileTexture, sfTrue);

	bgRectangle = sfRectangleShape_create();
	sfRectangleShape_setSize(bgRectangle, vector2f(1920.f, 1080.f));
	sfRectangleShape_setFillColor(bgRectangle, sfColor_fromRGB(6, 5, 13));

	mapHeight = 10;
	mapWidth = 10;

	block = malloc(mapHeight * sizeof(BlocksTileMap));
	for (int i = 0; i < mapWidth; i++)
	{
		block[i] = malloc(mapWidth * sizeof(BlocksTileMap));
	}
	
	for (int j = 0; j < mapHeight; j++)
	{
		for (int i = 0; i < mapWidth; i++)
		{
			block[j][i].id = i + (j * mapHeight);
			block[j][i].rect.width = 32;
			block[j][i].rect.height = 32;
			block[j][i].scale = vector2f(BLOCK_SIZE / 32, BLOCK_SIZE / 32);
			block[j][i].pos = vector2f(i * block[j][i].rect.width * block[j][i].scale.x, j * block[j][i].rect.height * block[j][i].scale.y);

			block[j][i].rect.left = map[j][i] % 8 * block[j][i].rect.width;
			block[j][i].rect.top = map[j][i] / 8 * block[j][i].rect.height;
			if (block[j][i].rect.left == 0) {
				block[j][i].rect.left = 7 * block[j][i].rect.width;
				block[j][i].rect.top -= block[j][i].rect.height;
			}
			else block[j][i].rect.left -= block[j][i].rect.width;


		}
	}

}

void updateMap()
{
	for (int j = 0; j < mapHeight; j++)
	{
		for (int i = 0; i < mapWidth; i++)
		{

		}
	}
}

void displayMap(sfRenderTexture* _texture)
{
	sfRenderTexture_drawRectangleShape(_texture, bgRectangle, NULL);
	for (int j = 0; j < mapHeight; j++)
	{
		for (int i = 0; i < mapWidth; i++)
		{
			sfSprite_setTextureRect(tile, block[j][i].rect);
			sfSprite_setScale(tile, block[j][i].scale);
			sfSprite_setPosition(tile, block[j][i].pos);
			sfRenderTexture_drawSprite(_texture, tile, NULL);
		}
	}
}

//sfBool collisionMapPlayer(sfFloatRect _sprite, int _direction, sfVector2f _vitesse)
//{
//
//	if (_direction == UP)
//	{
//		sfVector2i nextPosInTab = { _sprite.left / 32, (_sprite.top - _vitesse.y * getDeltaTime()) / 32 };
//		sfVector2i nextPosInTab2 = { (_sprite.left + _sprite.width) / 32, (_sprite.top - _vitesse.y * getDeltaTime()) / 32 };
//		//Collision type mur 
//		if (map[nextPosInTab.y][nextPosInTab.x] > 3 && map[nextPosInTab.y][nextPosInTab.x] < 9 || map[nextPosInTab.y][nextPosInTab.x] > 10 && map[nextPosInTab.y][nextPosInTab.x] < 13 ||
//			map[nextPosInTab2.y][nextPosInTab2.x] > 3 && map[nextPosInTab2.y][nextPosInTab2.x] < 9 || map[nextPosInTab2.y][nextPosInTab2.x] > 10 && map[nextPosInTab2.y][nextPosInTab2.x] < 13) // Choix des blocs à collision 
//		{
//			return sfTrue;
//		}
//	}
//
//	else if (_direction == DOWN)
//	{
//		sfVector2i nextPosInTab = { _sprite.left / 32, (_sprite.top + _sprite.height + _vitesse.y * getDeltaTime()) / 32 };
//		sfVector2i nextPosInTab2 = { (_sprite.left + _sprite.width) / 32, (_sprite.top + _sprite.height + _vitesse.y * getDeltaTime()) / 32 };
//		//Collision type mur
//		if (map[nextPosInTab.y][nextPosInTab.x] > 3 && map[nextPosInTab.y][nextPosInTab.x] < 9 || map[nextPosInTab.y][nextPosInTab.x] > 10 && map[nextPosInTab.y][nextPosInTab.x] < 13 ||
//			map[nextPosInTab2.y][nextPosInTab2.x] > 3 && map[nextPosInTab2.y][nextPosInTab2.x] < 9 || map[nextPosInTab2.y][nextPosInTab2.x] > 10 && map[nextPosInTab2.y][nextPosInTab2.x] < 13) // Choix des blocs à collision 
//		{
//			return sfTrue;
//		}
//	}
//
//	else if (_direction == LEFT)
//	{
//		sfVector2i nextPosInTab = { (_sprite.left - _vitesse.x * getDeltaTime()) / 32, (_sprite.top) / 32 };
//		sfVector2i nextPosInTab2 = { (_sprite.left - _vitesse.x * getDeltaTime()) / 32, (_sprite.top + _sprite.height) / 32 };
//		//Collision type mur
//		if (map[nextPosInTab.y][nextPosInTab.x] > 3 && map[nextPosInTab.y][nextPosInTab.x] < 9 || map[nextPosInTab.y][nextPosInTab.x] > 10 && map[nextPosInTab.y][nextPosInTab.x] < 13 ||
//			map[nextPosInTab2.y][nextPosInTab2.x] > 3 && map[nextPosInTab2.y][nextPosInTab2.x] < 9 || map[nextPosInTab2.y][nextPosInTab2.x] > 10 && map[nextPosInTab2.y][nextPosInTab2.x] < 13) // Choix des blocs à collision
//		{
//			return sfTrue;
//		}
//	}
//
//	else if (_direction == RIGHT)
//	{
//		sfVector2i nextPosInTab = { (_sprite.left + _sprite.width + _vitesse.x * getDeltaTime()) / 32, _sprite.top / 32 };
//		sfVector2i nextPosInTab2 = { (_sprite.left + _sprite.width + _vitesse.x * getDeltaTime()) / 32, (_sprite.top + _sprite.height) / 32 };
//		//Collision type mur
//		if (map[nextPosInTab.y][nextPosInTab.x] > 3 && map[nextPosInTab.y][nextPosInTab.x] < 9 || map[nextPosInTab.y][nextPosInTab.x] > 10 && map[nextPosInTab.y][nextPosInTab.x] < 13 ||
//			map[nextPosInTab2.y][nextPosInTab2.x] >3 && map[nextPosInTab2.y][nextPosInTab2.x] < 9 || map[nextPosInTab2.y][nextPosInTab2.x] > 10 && map[nextPosInTab2.y][nextPosInTab2.x] < 13) // Choix des blocs à collision
//		{
//			return sfTrue;
//		}
//	}
//
//	// Aucune collision
//	return sfFalse;
//}