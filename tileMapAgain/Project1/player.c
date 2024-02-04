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
sfBool isAnimFinished;
float moveTimer;
float waitMoveTimer;
int allIdles;

float birdMovementTimer;
float invertBirdMovement;

PlayerType playerFocused;
sfVector2f basePlayerPos;
PlayerType lastPlayerFocused;

sfBool resetTmpPos = sfFalse;

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
			player[i].type = FROG;
			player[i].origin = vector2f(16.f, 32.f);
			setPlayerPosInBlock(i, 3, 3);
			player[i].isGrounded = sfFalse;
		}
		else if (i == BIRD) {
			player[i].type = BIRD;
			player[i].origin = vector2f(16.f, 48.f);
			setPlayerPosInBlock(i, 1, 6);
		}
		player[i].rect = (sfIntRect){ 0, 0, 32, 32 };
		player[i].tmpPos = player[i].pos;

		player[i].wantedBloc = vector2i(0, 0);

		player[i].flip = sfFalse;
		player[i].frameX = 0;


		player[i].animTimer = 0.f;
		player[i].animState = IDLE;
		player[i].lastAnimState = IDLE;
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

	isAnimFinished = sfTrue;
	allIdles = 0;

	setViewFocus(FROG);
	setBasePlayerPos(FROG);
	lastPlayerFocused = FROG;

	birdMovementTimer = 0.f;
	invertBirdMovement = 1.f;
}

void updatePlayer()
{
	//applyGravity();
	allIdles = 0;
	moveTimer += getDeltaTime();
	//printf("%f, %f\n", player[FROG].pos.x, player[FROG].pos.y);
	//printf("%d, %d\n", player[FROG].currentBloc, player[FROG].wantedBloc);

	if (player[FROG].animState == IDLE && !resetTmpPos) {
		if (isPlayerGrounded(FROG)) player[FROG].isGrounded = sfTrue;
		else player[FROG].isGrounded = sfFalse;
	
		if (!player[FROG].isGrounded) {
			player[FROG].animState = FALL;
			setWantedBlockPos(FROG, player[FROG].animState);
			allowedToMove = sfFalse;
			setViewFocus(FROG);
		}
	}

	if ((sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp)) && allowedToMove) {
		player[BIRD].animState = JUMP;
		setWantedBlockPos(BIRD, player[BIRD].animState);
		setViewFocus(BIRD);
		if (!canPlayerGoThere(BIRD, player[BIRD].animState)) {
			player[BIRD].animState = IDLE;
		}
		//player[BIRD].flip = sfTrue;
	}
	else if ((sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown)) && allowedToMove) {
		player[BIRD].animState = FALL;
		setWantedBlockPos(BIRD, player[BIRD].animState);
		setViewFocus(BIRD);
		if (!canPlayerGoThere(BIRD, player[BIRD].animState)) {
			player[BIRD].animState = IDLE;
		}
		//player[BIRD].flip = sfFalse;
	}
	else if ((sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft)) && allowedToMove) {
		player[FROG].animState = RUN;
		player[FROG].flip = sfTrue;
		sfSprite_setScale(playerSprite, vector2f(-1.f * player[FROG].scale.x, 1.f * player[FROG].scale.y));
		setWantedBlockPos(FROG, player[FROG].animState);
		setViewFocus(FROG);
		if (!canPlayerGoThere(FROG, player[FROG].animState)) {
			player[FROG].animState = IDLE;
		}
	}
	else if ((sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight)) && allowedToMove) {
		player[FROG].animState = RUN;
		player[FROG].flip = sfFalse;
		sfSprite_setScale(playerSprite, vector2f(1.f * player[FROG].scale.x, 1.f * player[FROG].scale.y));
		setWantedBlockPos(FROG, player[FROG].animState);
		setViewFocus(FROG);
		if (!canPlayerGoThere(FROG, player[FROG].animState)) {
			player[FROG].animState = IDLE;
		}
	}
	//else {
	//	player[FROG].animState = IDLE;
	//	player[BIRD].animState = IDLE;
	//}



	for (int i = 0; i < nb_players; i++) {

		// INIT ANIMS
		if (player[i].animState != player[i].lastAnimState) {
			switch (player[i].animState) {
			case FALL:
				if (i == FROG) {
					sfSprite_setTexture(playerSprite, playerTextureFall, sfTrue);
				}
				else if (i == BIRD) {
					sfSprite_setTexture(player2Sprite, player2TextureFall, sfTrue);
				}
				break;
			case RUN:
				if (i == FROG) {
					sfSprite_setTexture(playerSprite, playerTextureRun, sfTrue);
				}
				break;
			case JUMP:
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

			//// ROTATION
			//if (i == FROG) {
			//	if (player[i].flip) sfSprite_setScale(playerSprite, vector2f(-1.f * player[i].scale.x, 1.f * player[i].scale.y));
			//	else if (!player[i].flip) sfSprite_setScale(playerSprite, vector2f(1.f * player[i].scale.x, 1.f * player[i].scale.y));
			//}
			//else if (i == BIRD) {
			//	if (player[i].flip) sfSprite_setScale(player2Sprite, vector2f(-1.f * player[i].scale.x, 1.f * player[i].scale.y));
			//	else if (!player[i].flip) sfSprite_setScale(player2Sprite, vector2f(1.f * player[i].scale.x, 1.f * player[i].scale.y));
			//}



			player[i].rect.top = 0;
			player[i].rect.left = 0;

			if (resetTmpPos) {
				player[i].tmpPos = player[i].pos;
				moveTimer = 0.f;
				waitMoveTimer = 0.f;
				isAnimFinished = sfFalse;
				resetTmpPos = sfFalse;
			}

			player[i].lastAnimState = player[i].animState;


			if (player[i].animState != IDLE) {
				player[i].tmpPos = player[i].pos;
				moveTimer = 0.f;
				waitMoveTimer = 0.f;
				isAnimFinished = sfFalse;
				//getCurrentBlockPos(FROG);
				//printf("%d.x, %d.y ; %d.x, %d.y\n", player[i].currentBloc.x, player[i].currentBloc.y, player[i].wantedBloc.x, player[i].wantedBloc.y);

			}

		}

		//if (canPlayerMove()) allowedToMove = sfTrue;

		//canMove
		if (player[i].animState == IDLE) allIdles++;
		//if (sfView_getCenter(gameView).x == player[i].pos.x && sfView_getCenter(gameView).y == player[i].pos.y) allIdles++;
		if (allIdles >= nb_players /*&& moveTimer >= 0.1*/ && (getViewTimer() >= VIEW_LERP_TIMER_DURATION || getViewFocus() == getLastPlayerFocused())) allowedToMove = sfTrue;
		else allowedToMove = sfFalse;



		//if (isAnimFinished && sfView_getCenter(gameView).x == player[i].pos.x && sfView_getCenter(gameView).y == player[i].pos.y) allowedToMove = sfTrue;
		//else allowedToMove = sfFalse;


		// MOVE
		if (player[i].animState != IDLE) {
			movePlayer(i, player[i].animState);
		}

		player[i].animTimer += getDeltaTime();



		// UPDATE ANIMS
		switch (player[i].animState) {
		case JUMP:
			//if (player[i].animTimer > 0.1f) {
			//	player[i].frameX++;
			//	if (player[i].frameX >= 9) player[i].frameX = 0;
			//	player[i].rect.left = player[i].frameX * player[i].rect.width;
			//	player[i].animTimer = 0.f;
			//}
			break;
		case FALL:
			//if (player[i].animTimer > 0.1f) {
			//	player[i].frameX++;
			//	if (player[i].frameX >= 9) player[i].frameX = 0;
			//	player[i].rect.left = player[i].frameX * player[i].rect.width;
			//	player[i].animTimer = 0.f;
			//}
			break;
		case RUN:
			if (player[i].animTimer > 0.1f/*ANIM_TIME_DURATION / 12.f*/) {
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
	}

	// Make the BIRD fly
	if (player[BIRD].animState == IDLE) birdMovementTimer += getDeltaTime();
	if (player[BIRD].lastAnimState == JUMP) {
		invertBirdMovement = 1.f;
		player[BIRD].origin.y = 48.f;
	}
	else if (player[BIRD].lastAnimState == FALL) {
		invertBirdMovement = -1.f;
		player[BIRD].origin.y = 48.f;
	}
	if (birdMovementTimer > ANIM_TIME_DURATION / 11.f * 2.f) {
		if (player[BIRD].origin.y > 56.f) invertBirdMovement = -1.f;
		if (player[BIRD].origin.y < 40.f) invertBirdMovement = 1.f;
		player[BIRD].origin.y += 1.f * invertBirdMovement;
		birdMovementTimer = 0.f;
	}



	sfSprite_setPosition(playerSprite, player[FROG].pos);
	sfSprite_setTextureRect(playerSprite, player[FROG].rect);
	sfSprite_setOrigin(player2Sprite, player[BIRD].origin);
	sfSprite_setPosition(player2Sprite, player[BIRD].pos);
	sfSprite_setTextureRect(player2Sprite, player[BIRD].rect);
}

void displayPlayer(sfRenderTexture* _texture)
{
	// +2 & -2 to smooth the pos with the 2pixel border
	//player[BIRD].pos.y += 2.f;
	//sfSprite_setPosition(player2Sprite, player[BIRD].pos);
	sfRenderTexture_drawSprite(_texture, player2Sprite, NULL);
	//player[BIRD].pos.y -= 2.f;

	//player[FROG].pos.y += 2.f;
	//sfSprite_setPosition(playerSprite, player[FROG].pos);
	sfRenderTexture_drawSprite(_texture, playerSprite, NULL);
	///player[FROG].pos.y -= 2.f;

}

sfBool canPlayerMove() // doesn't work but fck it
{
	////canMove
	//if (player[i].animState == IDLE) allIdles++;
	////if (sfView_getCenter(gameView).x == player[i].pos.x && sfView_getCenter(gameView).y == player[i].pos.y) allIdles++;
	//if (allIdles >= nb_players /*&& moveTimer >= 0.1*/) allowedToMove = sfTrue;
	//else allowedToMove = sfFalse;
	if (getViewTimer() >= VIEW_LERP_TIMER_DURATION) return sfTrue;
	return sfFalse;
}

sfBool canPlayerGoThere(PlayerType _type, Direction _direction)
{
	if (isBlockSolid(vector2i(player[_type].wantedBloc.x, player[_type].wantedBloc.y))) return sfFalse;
	return sfTrue;
}

sfBool isPlayerGrounded(PlayerType _type)
{
	sfVector2i iPos = getCurrentBlockPos(_type);
	sfVector2i underPos = iPos;
	underPos.y += 1; // one block below
	if (isBlockSolid(underPos)) return sfTrue;
	return sfFalse;
}

sfVector2i convertPosInBlock(sfVector2f _pos)
{
	return vector2i((int)_pos.x / (int)BLOCK_SIZE, (int)_pos.y / (int)BLOCK_SIZE - 1);
}

sfVector2f convertBlockInPos(sfVector2i _block)
{
	return vector2f((float)_block.x * BLOCK_SIZE, (float)_block.y * BLOCK_SIZE);
}

sfVector2i getCurrentBlockPos(PlayerType _type)
{
	sfVector2i v;
	//v = vector2i((int)player[_type].pos.x / (int)BLOCK_SIZE, (int)player[_type].pos.y / (int)BLOCK_SIZE - 1);
	v = convertPosInBlock(player[_type].pos);
	player[_type].currentBloc = v;
	return v;
}

void setWantedBlockPos(PlayerType _type, Direction _direction)
{
	sfVector2i v;
	sfVector2i add;
	switch (_direction) {
	case JUMP:
		add = vector2i(0, -1);
		break;
	case FALL:
		add = vector2i(0, 1);
		break;
	case RUN:
		if (!player[_type].flip) add = vector2i(1, 0);
		else if (player[_type].flip) add = vector2i(-1, 0);
		break;
	default:
		add = vector2i(0, 0);
		break;
	}
	v = getCurrentBlockPos(_type);
	v.x += add.x;
	v.y += add.y;
	player[_type].wantedBloc = v;
	return v;
}

sfVector2f getWantedBlockPos(PlayerType _type)
{
	return convertBlockInPos(player[_type].wantedBloc);
}

void applyGravity()
{
	//if (!collisionMapPlayer(player.fRect, FALL, AddVectors(player.acceleration, vector2f(1000.f, 1000.f)))) {
	//	if (player.acceleration.y > 0.05f) player.acceleration.y = 0.05f;
	//	player.pos = AddVectors(player.pos, player.acceleration);
	//}
	////player.pos = AddVectors(player.pos, player.acceleration);

}

void setPlayerPosInBlock(PlayerType _type, int _x, int _y)
{
	//should work like that but shifting the bird origin to 48 instead of 32 fucked up everything so i'll just keeping it like that

	//player[_type].pos.x = (int)BLOCK_SIZE * _x + (int)player[_type].origin.x * 2;
	//player[_type].pos.y = (int)BLOCK_SIZE * _y + (int)player[_type].origin.y * 2;
	player[_type].pos.x = (int)BLOCK_SIZE * _x + 16 * 2;
	player[_type].pos.y = (int)BLOCK_SIZE * _y + 32 * 2;
}

void movePlayer(PlayerType _type, Direction _direction)
{
	//isAnimFinished = sfFalse;
	switch (_type) {
	case FROG:
		
		switch (_direction) {
		case RUN:
			if (!player[_type].flip) player[_type].pos.x = Lerp(player[_type].tmpPos.x, player[_type].tmpPos.x + BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			else if (player[_type].flip) player[_type].pos.x = Lerp(player[_type].tmpPos.x, player[_type].tmpPos.x - BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			if (moveTimer >= ANIM_TIME_DURATION) {
				isAnimFinished = sfTrue;
				moveTimer = 0.f;
				player[_type].animState = IDLE;
				setPlayerPosInBlock(_type, player[_type].wantedBloc.x, player[_type].wantedBloc.y);
			}
			break;
		case FALL:
			player[_type].pos.y = Lerp(player[_type].tmpPos.y, player[_type].tmpPos.y + BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			if (moveTimer >= ANIM_TIME_DURATION) {
				resetTmpPos = sfTrue;
				isAnimFinished = sfTrue;
				moveTimer = 0.f;
				setPlayerPosInBlock(_type, player[_type].wantedBloc.x, player[_type].wantedBloc.y);
				player[_type].animState = IDLE;
			}
			break;
		default:
			break;
		}

		break;
	case BIRD:

		switch (_direction) {
		case JUMP:
			player[_type].pos.y = Lerp(player[_type].tmpPos.y, player[_type].tmpPos.y - BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			if (moveTimer >= ANIM_TIME_DURATION) {
				isAnimFinished = sfTrue;
				moveTimer = 0.f;
				player[_type].animState = IDLE;
				setPlayerPosInBlock(_type, player[_type].wantedBloc.x, player[_type].wantedBloc.y);
			}
			break;
		case FALL:
			player[_type].pos.y = Lerp(player[_type].tmpPos.y, player[_type].tmpPos.y + BLOCK_SIZE, moveTimer * 1.f / ANIM_TIME_DURATION);
			if (moveTimer >= ANIM_TIME_DURATION) {
				isAnimFinished = sfTrue;
				moveTimer = 0.f;
				player[_type].animState = IDLE;
				setPlayerPosInBlock(_type, player[_type].wantedBloc.x, player[_type].wantedBloc.y);
			}
			break;
		default:
			break;
		}

		break;
	default:
		break;
	}
}

void setViewFocus(PlayerType _type)
{
	playerFocused = _type;
	setBasePlayerPos(_type);
}

PlayerType getViewFocus()
{
	return playerFocused;
}

void setLastPlayerFocused(PlayerType _type)
{
	lastPlayerFocused = _type;
}

PlayerType getLastPlayerFocused()
{
	return lastPlayerFocused;
}

void setBasePlayerPos(PlayerType _type)
{
	basePlayerPos = player[_type].pos;
	setViewTimer(0.f);
}

sfVector2f getBasePlayerPos()
{
	return basePlayerPos;
}

sfVector2f getPlayerPosInBounds(PlayerType _type, sfVector2f _ratio)
{
	sfVector2f v = player[_type].pos;

	// these wouldn't work dynamicly, (update)it prolly would in fact
	if (v.x < _ratio.x / 2.f) v.x = _ratio.x / 2.f;
	if (v.x > (float)mapWidth * BLOCK_SIZE - _ratio.x / 2.f) v.x = (float)mapWidth * BLOCK_SIZE - _ratio.x / 2.f;
	if (v.y < _ratio.y / 2.f) v.y = _ratio.y / 2.f;
	if (v.y > (float)mapHeight * BLOCK_SIZE - _ratio.y / 2.f) v.y = (float)mapHeight * BLOCK_SIZE - _ratio.y / 2.f;

	return v;
}

Direction getPlayerDirection(PlayerType _type)
{
	return player[_type].animState;
}

