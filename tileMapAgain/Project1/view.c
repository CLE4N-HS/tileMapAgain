#include "view.h"

float viewLerpTimer;
sfVector2f gameViewPos;
sfVector2f gameViewRatio;

void initView()
{
	gameView = sfView_create();
	sfView_setCenter(gameView, player[FROG].pos);
	gameViewRatio = vector2f(MAP_WIDTH_IN_PIXELS / 3.f, MAP_HEIGHT_IN_PIXELS / 3.f);
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
	sfView_setCenter(gameView, gameViewPos);
	//if (gameViewPos.x < gameViewRatio.x)
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
