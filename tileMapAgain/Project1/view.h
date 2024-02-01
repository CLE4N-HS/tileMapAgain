#pragma once
#include "player.h"
#include "map.h"
#include "math.h"

#define VIEW_LERP_TIMER_DURATION 1.f

sfView* gameView;

void initView();
void updateView();
void displayView(sfRenderWindow* _window);
sfVector2f lerpView(sfVector2f _basePos, sfVector2f _neededPos, float _timer);

void setViewTimer();
float getViewTimer();