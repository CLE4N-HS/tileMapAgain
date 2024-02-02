#include "view.h"

float viewLerpTimer;
sfVector2f gameViewPos;
sfVector2f gameViewRatio;

void initView()
{
	gameView = sfView_create();
	gameViewPos = player[FROG].pos;
	sfView_setCenter(gameView, gameViewPos);
	gameViewRatio = vector2f(1920.f / 3.f, 1080.f / 3.f);
	sfView_setSize(gameView, gameViewRatio);

	viewLerpTimer = VIEW_LERP_TIMER_DURATION;
}

void updateView()
{
	viewLerpTimer += getDeltaTime();
	if (viewLerpTimer > VIEW_LERP_TIMER_DURATION) viewLerpTimer = VIEW_LERP_TIMER_DURATION;
	//switch (getViewFocus()) {
	//case FROG:
	//	gameViewPos = lerpView(getPlayerPosInBounds(getLastPlayerFocused(), gameViewRatio), getPlayerPosInBounds(FROG, gameViewRatio), viewLerpTimer);
	//	if (viewLerpTimer >= VIEW_LERP_TIMER_DURATION) setLastPlayerFocused(FROG);
	//	break;
	//case BIRD:
	//	gameViewPos = lerpView(getPlayerPosInBounds(getLastPlayerFocused(), gameViewRatio), getPlayerPosInBounds(BIRD, gameViewRatio), viewLerpTimer);
	//	if (viewLerpTimer >= VIEW_LERP_TIMER_DURATION) setLastPlayerFocused(BIRD);
	//	break;
	//default:
	//	break;
	//}

	gameViewPos = lerpView(getPlayerPosInBounds(getLastPlayerFocused(), gameViewRatio), getPlayerPosInBounds(getViewFocus(), gameViewRatio), viewLerpTimer);
	if (viewLerpTimer >= VIEW_LERP_TIMER_DURATION) setLastPlayerFocused(getViewFocus());

	sfView_setCenter(gameView, gameViewPos);
}

void displayView(sfRenderWindow* _window)
{
	sfRenderWindow_setView(_window, gameView);
}

sfVector2f lerpView(sfVector2f _basePos, sfVector2f _neededPos, float _timer)
{
	//if (gameViewPos.x < gameViewRatio.x) {
	//	//viewLerpTimer = VIEW_LERP_TIMER_DURATION;
	//	if (gameViewPos.y < gameViewRatio.y / 2.f) { // top left
	//		_neededPos = DivideVector(gameViewRatio, 2.f);
	//		_basePos = _neededPos;
	//		//viewLerpTimer = VIEW_LERP_TIMER_DURATION;
	//	}
	//	else if (gameViewPos.y > 1080.f - gameViewRatio.y / 2.f) { // bottom left
	//		_neededPos.x = gameViewRatio.x / 2.f;
	//		_neededPos.y = 1080.f - gameViewRatio.y / 2.f;
	//		_basePos = _neededPos;
	//		//viewLerpTimer = VIEW_LERP_TIMER_DURATION;
	//	}
	//	else { // left
	//		_neededPos.x = gameViewRatio.x / 2.f;
	//		_neededPos.y = player[getViewFocus()].pos.y;
	//		_basePos.x = _neededPos.x;
	//	}
	//	//return gameViewPos;
	//}
	return LerpVector(_basePos, _neededPos, _timer * 1.f / VIEW_LERP_TIMER_DURATION);
}

void setViewTimer(float _time)
{
	viewLerpTimer = _time;
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
