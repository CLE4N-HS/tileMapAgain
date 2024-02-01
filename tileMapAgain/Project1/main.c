#include "tools.h"

void main(){
	sfVideoMode mode = { 1920, 1080, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfFullscreen, NULL);

	sfSprite* allSprites = sfSprite_create();
	sfRenderTexture* renderTexture = sfRenderTexture_create(1920, 1080, sfFalse);
	sfTexture* allTextures;

	initTools();
	initPlayer();
	initView();
	initMap();

	sfEvent event;

	//sfWindow_setFramerateLimit(window, 60);

	while (sfRenderWindow_isOpen(window))
	{
		restartClock();
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
			{
				sfRenderWindow_close(window);
			}
		}

		updateMap();
		updatePlayer();
		updateView();


		sfRenderTexture_clear(renderTexture, sfBlue);

		displayMap(renderTexture);
		displayPlayer(renderTexture);
		displayView(window);


		sfRenderTexture_display(renderTexture);

		allTextures = sfRenderTexture_getTexture(renderTexture);
		sfSprite_setTexture(allSprites, allTextures, sfFalse);

		sfRenderWindow_clear(window, sfBlue);

		sfRenderWindow_drawSprite(window, allSprites, NULL);

		sfRenderWindow_display(window);

		if (sfKeyboard_isKeyPressed(sfKeyEscape) || sfMouse_isButtonPressed(sfMouseRight) /*&& sfWindow_hasFocus(window)*/) exit(EXIT_SUCCESS);

		
	}
}