#include "player.h"

sfSprite* playerSprite;
sfTexture* playerTextureIdle;
sfTexture* playerTextureRun;
sfTexture* playerTextureJump;
sfTexture* playerTextureFall;

sfSprite* player2Sprite;
sfTexture* player2TextureIdle;
sfTexture* player2TextureRun;
sfTexture* player2TextureJump;
sfTexture* player2TextureFall;

sfBool allowedToMove;
float moveTimer;
float waitMoveTimer;


void initPlayer()
{
	playerSprite = sfSprite_create();
	playerTextureIdle = sfTexture_createFromFile(FROG_PATH"Idle (32x32).png", NULL);
	playerTextureRun = sfTexture_createFromFile(FROG_PATH"Run (32x32).png", NULL);
	playerTextureJump = sfTexture_createFromFile(FROG_PATH"Jump (32x32).png", NULL);
	playerTextureFall = sfTexture_createFromFile(FROG_PATH"Fall (32x32).png", NULL);
	sfSprite_setTexture(playerSprite, playerTextureIdle, sfTrue);

	player2Sprite = sfSprite_create();
	player2TextureIdle = sfTexture_createFromFile(VIRTUALGUY_PATH"Idle (32x32).png", NULL);
	player2TextureRun = sfTexture_createFromFile(VIRTUALGUY_PATH"Run (32x32).png", NULL);
	player2TextureJump = sfTexture_createFromFile(VIRTUALGUY_PATH"Jump (32x32).png", NULL);
	player2TextureFall = sfTexture_createFromFile(VIRTUALGUY_PATH"Fall (32x32).png", NULL);
	sfSprite_setTexture(player2Sprite, player2TextureIdle, sfTrue);

	nb_players = 2;
	player = malloc(nb_players * sizeof(Player));

	for (int i = 0; i < nb_players; i++)
	{
		player[i].scale = vector2f(1.f, 1.f);
		if (i == FROG) {
			player[i].origin = vector2f(16.f, 32.f);
			player[i].pos = vector2f(2.f * BLOCK_SIZE - player[i].origin.x * 2.f, 5.f * BLOCK_SIZE);
		}
		else if (i == BIRD) {
			player[i].origin = vector2f(16.f, 32.f);
			player[i].pos = vector2f(1.f * BLOCK_SIZE - player[i].origin.x * 2.f, 4.f * BLOCK_SIZE);
		}
		player[i].rect = (sfIntRect){ 0, 0, 32, 32 };



		player[i].flip = sfFalse;
		player[i].frameX = 0;


		player[i].speed = vector2f(100.f, 100.f);
		player[i].animTimer = 0.f;
		player[i].animState = IDLE;
		player[i].gravity = 9.81f;
		player[i].acceleration = vector2f(0.f, 10.f);
	}

	sfSprite_setOrigin(playerSprite, player[FROG].origin);
	sfSprite_setTextureRect(playerSprite, player[FROG].rect);
	sfSprite_setScale(playerSprite, player[FROG].scale);
	sfSprite_setPosition(playerSprite, player[FROG].pos);
	sfSprite_setOrigin(player2Sprite, player[BIRD].origin);
	sfSprite_setScale(player2Sprite, player[BIRD].scale);
	sfSprite_setTextureRect(player2Sprite, player[BIRD].rect);
	sfSprite_setPosition(player2Sprite, player[BIRD].pos);

	allowedToMove = sfTrue;
	moveTimer = 0.f;
	waitMoveTimer = 0.f;
}

void updatePlayer()
{
	//player[FROG].acceleration.y += getDeltaTime();
	//
	//if (sfKeyboard_isKeyPressed(sfKeySpace) && player[FROG].allowedToJump) {
	//	player[FROG].pos.y -= 10.f;
	//	player[FROG].acceleration.y = -0.2f;
	//	player[FROG].allowedToJump = sfFalse;
	//}
	//if (!sfKeyboard_isKeyPressed(sfKeySpace)) player[FROG].allowedToJump = sfTrue;
	//
	//applyGravity();

	if ((sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp)) && allowedToMove) {
		player[BIRD].animState = UP;
	}
	else if ((sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown)) && allowedToMove) {
		player[BIRD].animState = DOWN;
	}
	else if ((sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft)) && allowedToMove) {
		player[FROG].animState = RUN;
		player[FROG].flip = sfTrue;
	}
	else if ((sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight)) && allowedToMove) {
		player[FROG].animState = RUN;
		player[FROG].flip = sfFalse;
	}
	//else {
	//	player[FROG].animState = IDLE;
	//	player[BIRD].animState = IDLE;
	//}

	for (int i = 0; i < nb_players; i++) {

		// INIT ANIMS
		if (player[i].animState != player[i].lastAnimState) {
			switch (player[i].animState) {
			case DOWN:
				if (i == BIRD) {
					sfSprite_setTexture(player2Sprite, player2TextureFall, sfTrue);
				}
				break;
			case RUN:
				if (i == FROG) {
					sfSprite_setTexture(playerSprite, playerTextureRun, sfTrue);
				}
				break;
			case UP:
				if (i == BIRD) {
					sfSprite_setTexture(player2Sprite, player2TextureJump, sfTrue);
				}
				break;
			case IDLE:
				if (i == FROG) {
					sfSprite_setTexture(playerSprite, playerTextureIdle, sfTrue);
				}
				else if (i == BIRD) {
					sfSprite_setTexture(player2Sprite, player2TextureIdle, sfTrue);
				}
				break;
			default:
				break;
			}

			if (player[i].flip) {
				sfSprite_setScale(playerSprite, vector2f(-1.f * player[i].scale.x, 1.f * player[i].scale.y));
			}
			else {
				sfSprite_setScale(playerSprite, vector2f(1.f * player[i].scale.x, 1.f * player[i].scale.y));
			}

			player[i].rect.top = 0;
			player[i].rect.left = 0;
			player[i].tmpPos = player[i].pos;

			player[i].lastAnimState = player[i].animState;

			if (player[i].animState != IDLE) {
				allowedToMove = sfFalse;
				moveTimer = 0.f;
				waitMoveTimer = 0.f;
			}

		}

		player[i].animTimer += getDeltaTime();
		moveTimer += getDeltaTime();


		// MOVE
		if (player[i].animState != IDLE) {
			movePlayer(i, player[i].animState);
		}
		printf("%d\n", player[FROG].animState);

		// UPDATE ANIMS
		switch (player[i].animState) {
		case UP:
			//if (player[i].animTimer > 0.1f) {
			//	player[i].frameX++;
			//	if (player[i].frameX >= 9) player[i].frameX = 0;
			//	player[i].rect.left = player[i].frameX * player[i].rect.width;
			//	player[i].animTimer = 0.f;
			//}
			break;
		case DOWN:
			//if (player[i].animTimer > 0.1f) {
			//	player[i].frameX++;
			//	if (player[i].frameX >= 9) player[i].frameX = 0;
			//	player[i].rect.left = player[i].frameX * player[i].rect.width;
			//	player[i].animTimer = 0.f;
			//}
			break;
		case RUN:
			if (player[i].animTimer > 0.1f) {
				player[i].frameX++;
				if (player[i].frameX >= 12) player[i].frameX = 0;
				player[i].rect.left = player[i].frameX * player[i].rect.width;
				player[i].animTimer = 0.f;
			}
			break;
		case IDLE:
			if (player[i].animTimer > 0.1f) {
				player[i].frameX++;
				if (player[i].frameX >= 11) player[i].frameX = 0;
				player[i].rect.left = player[i].frameX * player[i].rect.width;
				player[i].animTimer = 0.f;
			}
			break;
		default:
			break;
		}


		//if (player[i].pos.x < 0 + player[i].origin.x) player[i].pos.x = 0 + player[i].origin.x;
		//if (player[i].pos.y < 0 + player[i].origin.y) player[i].pos.y = 0 + player[i].origin.y;
		//if (player[i].pos.x > MAP_WIDTH * BLOCK_SIZE - player[i].origin.y) player[i].pos.x = MAP_WIDTH * BLOCK_SIZE - player[i].origin.x;
		//if (player[i].pos.y > MAP_HEIGHT * BLOCK_SIZE - player[i].origin.y) player[i].pos.y = MAP_HEIGHT * BLOCK_SIZE - player[i].origin.y;



	}

	sfSprite_setPosition(playerSprite, player[FROG].pos);
	sfSprite_setTextureRect(playerSprite, player[FROG].rect);
	sfSprite_setPosition(player2Sprite, player[BIRD].pos);
	sfSprite_setTextureRect(player2Sprite, player[BIRD].rect);
}

void displayPlayer(sfRenderTexture* _texture)
{
	sfRenderTexture_drawSprite(_texture, player2Sprite, NULL);
	sfRenderTexture_drawSprite(_texture, playerSprite, NULL);
}

void applyGravity()
{
	//if (!collisionMapPlayer(player.fRect, DOWN, AddVectors(player.acceleration, vector2f(1000.f, 1000.f)))) {
	//	if (player.acceleration.y > 0.05f) player.acceleration.y = 0.05f;
	//	player.pos = AddVectors(player.pos, player.acceleration);
	//}
	////player.pos = AddVectors(player.pos, player.acceleration);

}

void setPlayerInBlock(PlayerType _type, int _x, int _y)
{

}

void movePlayer(PlayerType _type, Direction _direction)
{
	switch (_type) {
	case FROG:
		
		switch (_direction) {
		case RUN:
			if (!player[FROG].flip) player[FROG].pos.x = Lerp(player[FROG].tmpPos.x, player[FROG].tmpPos.x + BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			else if (player[FROG].flip) player[FROG].pos.x = Lerp(player[FROG].tmpPos.x, player[FROG].tmpPos.x - BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			if (moveTimer >= ANIM_TIME_DURATION) {
				allowedToMove = sfTrue;
				moveTimer = 0.f;
				player[FROG].animState = IDLE;
			}
			break;
		default:
			break;
		}

		break;
	case BIRD:
		break;
	default:
		break;
	}
}
