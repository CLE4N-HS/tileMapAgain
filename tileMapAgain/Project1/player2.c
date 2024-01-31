//#include "player2.h"
//
//
//
//
//void initPlayer2()
//{
//
//	player2Sprite = sfSprite_create();
//	player2TextureIdle = sfTexture_createFromFile(VIRTUALGUY_PATH"Idle (32x32).png", NULL);
//	player2TextureRun = sfTexture_createFromFile(VIRTUALGUY_PATH"Run (32x32).png", NULL);
//	player2TextureJump = sfTexture_createFromFile(VIRTUALGUY_PATH"Jump (32x32).png", NULL);
//	player2TextureFall = sfTexture_createFromFile(VIRTUALGUY_PATH"Fall (32x32).png", NULL);
//	sfSprite_setTexture(player2Sprite, player2TextureIdle, sfTrue);
//
//	player2.rect = (sfIntRect){ 0, 0, 32, 32 };
//	sfSprite_setTextureRect(player2Sprite, player2.rect);
//
//	player2.origin = vector2f(16.f, 16.f);
//	sfSprite_setOrigin(player2Sprite, player2.origin);
//
//	player2.scale = vector2f(1.f, 1.f);
//	sfSprite_setScale(player2Sprite, player2.scale);
//	player2.flip = sfFalse;
//
//	player2.pos = vector2f(150.f, 50.f);
//	sfSprite_setPosition(player2Sprite, player2.pos);
//
//	player2.speed = vector2f(100.f, 100.f);
//	player2.animTimer = 0.f;
//	player2.gravity = 9.81f;
//	player2.acceleration = vector2f(0.f, 10.f);
//
//}
//
//void updatePlayer2()
//{
//	player2.fRect = sfSprite_getGlobalBounds(player2Sprite);
//
//	//player2.velocity.y += getDeltaTime() * 100000.f;
//	player2.acceleration.y += getDeltaTime();
//
//	if (sfKeyboard_isKeyPressed(sfKeySpace) && player2.allowedToJump) {
//		player2.pos.y -= 10.f;
//		player2.acceleration.y = -0.2f;
//		player2.allowedToJump = sfFalse;
//	}
//	if (!sfKeyboard_isKeyPressed(sfKeySpace)) player2.allowedToJump = sfTrue;
//
//	//applyGravity();
//
//	if (sfKeyboard_isKeyPressed(sfKeyZ) || sfKeyboard_isKeyPressed(sfKeyUp)) {
//		player2AnimState = UP2;
//		if (!collisionMapPlayer(player2.fRect, player2AnimState, player2.speed)) player2.pos.y -= getDeltaTime() * player2.speed.y;
//	}
//	else if (sfKeyboard_isKeyPressed(sfKeyS) || sfKeyboard_isKeyPressed(sfKeyDown)) {
//		player2AnimState = DOWN2;
//		if (!collisionMapPlayer(player2.fRect, player2AnimState, player2.speed)) player2.pos.y += getDeltaTime() * player2.speed.y;
//	}
//	//else if (sfKeyboard_isKeyPressed(sfKeyQ) || sfKeyboard_isKeyPressed(sfKeyLeft)) {
//	//	player2AnimState = LEFT2;
//	//	if (!collisionMapPlayer(player2.fRect, player2AnimState, player2.speed)) player2.pos.x -= getDeltaTime() * player2.speed.x;
//	//}
//	//else if (sfKeyboard_isKeyPressed(sfKeyD) || sfKeyboard_isKeyPressed(sfKeyRight)) {
//	//	player2AnimState = RIGHT2;
//	//	if (!collisionMapPlayer(player2.fRect, player2AnimState, player2.speed)) player2.pos.x += getDeltaTime() * player2.speed.x;
//	//}
//	else {
//		player2AnimState = IDLE2;
//	}
//
//	if (player2AnimState != player2LastAnimState) {
//		switch (player2AnimState)
//		{
//		case UP2:
//			sfSprite_setTexture(player2Sprite, player2TextureJump, sfTrue);
//			player2.flip = sfFalse;
//			break;
//		case DOWN2:
//			sfSprite_setTexture(player2Sprite, player2TextureFall, sfTrue);
//			player2.flip = sfFalse;
//			break;
//		case LEFT2:
//			break;
//		case RIGHT2:
//			break;
//		case IDLE2:
//			sfSprite_setTexture(player2Sprite, player2TextureIdle, sfTrue);
//			player2.flip = sfFalse;
//			break;
//		default:
//			break;
//		}
//
//		if (player2.flip) {
//			sfSprite_setScale(player2Sprite, vector2f(-1.f, 1.f));
//		}
//		else {
//			sfSprite_setScale(player2Sprite, vector2f(1.f, 1.f));
//		}
//
//		player2.rect.top = 0;
//		player2.rect.left = 0;
//
//		player2LastAnimState = player2AnimState;
//	}
//
//	player2.animTimer += getDeltaTime();
//
//	switch (player2AnimState)
//	{
//	case UP2:
//		//if (player2.animTimer > 0.1f) {
//		//	player2.frameX++;
//		//	if (player2.frameX >= 9) player2.frameX = 0;
//		//	player2.rect.left = player2.frameX * player2.rect.width;
//		//	player2.animTimer = 0.f;
//		//}
//		break;
//	case DOWN2:
//		//if (player2.animTimer > 0.1f) {
//		//	player2.frameX++;
//		//	if (player2.frameX >= 12) player2.frameX = 0;
//		//	player2.rect.left = player2.frameX * player2.rect.width;
//		//	player2.animTimer = 0.f;
//		//}
//		break;
//	case LEFT2:
//		//if (player2.animTimer > 0.1f) {
//		//	player2.frameX++;
//		//	if (player2.frameX >= 12) player2.frameX = 0;
//		//	player2.rect.left = player2.frameX * player2.rect.width;
//		//	player2.animTimer = 0.f;
//		//}
//		break;
//	case RIGHT2:
//		//if (player2.animTimer > 0.1f) {
//		//	player2.frameX++;
//		//	if (player2.frameX >= 9) player2.frameX = 0;
//		//	player2.rect.left = player2.frameX * player2.rect.width;
//		//	player2.animTimer = 0.f;
//		//}
//		break;
//	case IDLE2:
//		if (player2.animTimer > 0.1f) {
//			player2.frameX++;
//			if (player2.frameX >= 11) player2.frameX = 0;
//			player2.rect.left = player2.frameX * player2.rect.width;
//			player2.animTimer = 0.f;
//		}
//		break;
//	default:
//		break;
//	}
//
//	if (player2.pos.x < 0 + player2.origin.x) player2.pos.x = 0 + player2.origin.x;
//	if (player2.pos.y < 0 + player2.origin.y) player2.pos.y = 0 + player2.origin.y;
//	if (player2.pos.x > MAP_WIDTH * BLOCK_SIZE - player2.origin.y) player2.pos.x = MAP_WIDTH * BLOCK_SIZE - player2.origin.x;
//	if (player2.pos.y > MAP_HEIGHT * BLOCK_SIZE - player2.origin.y) player2.pos.y = MAP_HEIGHT * BLOCK_SIZE - player2.origin.y;
//
//
//	sfSprite_setPosition(player2Sprite, player2.pos);
//	sfSprite_setTextureRect(player2Sprite, player2.rect);
//}
//
//void displayPlayer2(sfRenderTexture* _texture)
//{
//	sfRenderTexture_drawSprite(_texture, player2Sprite, NULL);
//}
//
////void applyGravity()
////{
////	if (!collisionMapplayer2(player2.fRect, DOWN, AddVectors(player2.acceleration, vector2f(1000.f, 1000.f)))) {
////		if (player2.acceleration.y > 0.05f) player2.acceleration.y = 0.05f;
////		player2.pos = AddVectors(player2.pos, player2.acceleration);
////	}
////	//player2.pos = AddVectors(player2.pos, player2.acceleration);
////
////}
