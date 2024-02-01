#pragma once
#include "tools.h"

#define ANIM_TIME_DURATION 0.25f

typedef enum Direction Direction;
typedef enum Direction {
	JUMP,
	FALL,
	RUN,
	IDLE,
	NOCHEATCODE
}Direction;

typedef enum PlayerType {
	FROG = 0,
	BIRD,
	NB_TYPES
}PlayerType;

typedef struct Player {
	PlayerType type;
	sfIntRect rect;
	sfFloatRect fRect;
	int frameX;
	float animTimer;
	sfVector2f origin;
	sfVector2f scale;
	sfBool flip;
	sfVector2f pos;
	sfVector2f tmpPos;
	sfVector2i currentBloc;
	sfVector2i wantedBloc;
	sfVector2f speed;
	Direction animState;
	Direction lastAnimState;
	float gravity;
	sfVector2f acceleration;
	sfBool allowedToJump;
	sfBool allowedToWalk;
}Player;
Player* player;

int nb_players;

void initPlayer();
void updatePlayer();
void displayPlayer(sfRenderTexture* _texture);
sfVector2i getCurrentBlockPos(PlayerType _type);
sfVector2i setWantedBlockPos(PlayerType _type, Direction _direction);
void setPlayerPosInBlock(PlayerType _type, int _x, int _y);
void movePlayer(PlayerType _type, Direction _direction);
void setViewFocus(PlayerType _type);
PlayerType* getViewFocus();
void applyGravity();