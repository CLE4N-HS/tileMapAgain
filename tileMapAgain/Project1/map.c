#include "map.h"

char map[MAP_WIDTH][MAP_HEIGHT] = { {1,1,1,1,1,1,1,5,1,1},
									{1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1},
									{1,1,1,1,1,1,1,1,1,1},
									{5,1,1,1,1,1,1,1,1,1},
									{5,5,5,5,5,5,5,5,5,5},
									{5,5,5,5,5,5,5,5,5,5},
									{5,5,5,5,5,5,5,5,5,5},
									{5,5,5,5,5,5,5,5,5,5},
									{5,5,5,5,5,5,5,5,5,5} };

sfSprite* tile;
sfTexture* tileTexture;

void initMap()
{
	tile = sfSprite_create();
	tileTexture = sfTexture_createFromFile(TEXTURE_PATH"tileset1.png", NULL);
	sfSprite_setTexture(tile, tileTexture, sfTrue);

	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			block[j][i].id = i + (j * MAP_HEIGHT);
			block[j][i].rect.top = 0;
			block[j][i].rect.width = 32;
			block[j][i].rect.height = 32;
			block[j][i].scale = vector2f(BLOCK_SIZE / 32, BLOCK_SIZE / 32);
			block[j][i].pos = vector2f(i * block[j][i].rect.width * block[j][i].scale.x, j * block[j][i].rect.height * block[j][i].scale.y);
			switch (map[j][i])
			{
			case 0:
				block[j][i].rect.left = 0;
				break;
			case 1:
				block[j][i].rect.left = block[j][i].rect.width;
				break;
			case 5:
				block[j][i].rect.left = block[j][i].rect.width * 5;
				break;
			default:
				break;
			}

			sfSprite_setScale(tile, block[j][i].scale);


		}
	}

}

void updateMap()
{
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{

		}
	}
}

void displayMap(sfRenderTexture* _texture)
{
	for (int j = 0; j < MAP_HEIGHT; j++)
	{
		for (int i = 0; i < MAP_WIDTH; i++)
		{
			sfSprite_setTextureRect(tile, block[j][i].rect);
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