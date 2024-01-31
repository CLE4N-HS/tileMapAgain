#include "view.h"

sfView* gameView;

void initView()
{
	gameView = sfView_create();
	sfView_setCenter(gameView, vector2f(960.f / 3.f, 540.f / 3.f));
	sfView_setSize(gameView, vector2f(1920.f / 3.f, 1080.f / 3));
}

void updateView()
{
	//sfView_setCenter(gameView, vector2f(player.pos.x, player.pos.y));
}

void displayView(sfRenderWindow* _window)
{
	sfRenderWindow_setView(_window, gameView);
}
