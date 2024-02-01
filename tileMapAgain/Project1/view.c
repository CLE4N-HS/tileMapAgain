#include "view.h"

float viewLerpTimer;
sfVector2f gameViewPos;
sfVector2f gameViewRatio;

void initView()
{
	gameView = sfView_create();
	sfView_setCenter(gameView, player[FROG].pos);
	gameViewRatio = vector2f(1920 / 3.f, 1080 / 3.f);
	sfView_setSize(gameView, gameViewRatio);

	viewLerpTimer = VIEW_LERP_TIMER_DURATION;
}

void updateView()
{
	viewLerpTimer += getDeltaTime();
	if (viewLerpTimer > VIEW_LERP_TIMER_DURATION) viewLerpTimer = VIEW_LERP_TIMER_DURATION;
	switch (getViewFocus()) {
	case FROG:
		//sfView_setCenter(gameView, lerpView(getBasePlayerPos(), player[FROG].pos, viewLerpTimer));
		gameViewPos = lerpView(player[getLastPlayerFocused()].pos, player[FROG].pos, viewLerpTimer);
		if (viewLerpTimer >= VIEW_LERP_TIMER_DURATION) setLastPlayerFocused(FROG);
		break;
	case BIRD:
		//sfView_setCenter(gameView, lerpView(getBasePlayerPos(), player[BIRD].pos, viewLerpTimer));
		gameViewPos = lerpView(player[getLastPlayerFocused()].pos, player[BIRD].pos, viewLerpTimer);
		if (viewLerpTimer >= VIEW_LERP_TIMER_DURATION) setLastPlayerFocused(BIRD);
		break;
	default:
		break;
	}

	if (gameViewPos.x < gameViewRatio.x) {
		if (gameViewPos.y < gameViewRatio.y) gameViewPos = DivideVector(gameViewRatio, 2.f);
		else if (gameViewPos.y > 1080.f - gameViewRatio.y) {
			gameViewPos.x = gameViewRatio.x / 2.f;
			gameViewPos.y = 1080.f - gameViewRatio.y;
		}
		else {
			gameViewPos.x = gameViewRatio.x / 2.f;
			gameViewPos.y = player[getViewFocus()].pos.y;
		}

	}
	//if (gameViewPos.y < gameViewRatio.y) {
	//	if (gameViewPos.x < gameViewRatio.x) gameViewPos = DivideVector(gameViewRatio, 2.f);
	//}

	sfView_setCenter(gameView, gameViewPos);
	sfView_setCenter(gameView, player[getViewFocus()].pos);
}

void displayView(sfRenderWindow* _window)
{
	sfRenderWindow_setView(_window, gameView);
}

sfVector2f lerpView(sfVector2f _basePos, sfVector2f _neededPos, float _timer)
{
	return LerpVector(_basePos, _neededPos, _timer * 1 / VIEW_LERP_TIMER_DURATION);
}

void setViewTimer()
{
	viewLerpTimer = 0.f;
}

float getViewTimer()
{
	return viewLerpTimer;
}

//sfVector2f getPlayerPosInBounds(PlayerType _type)
//{
//	sfVector2f v = player[_type].pos;
//	//if (v.x < gameViewRatio.x)
//	return v;
//}
