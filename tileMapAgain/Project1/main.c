#include "tools.h"

void main(){
	sfVideoMode mode = { 1920, 1080, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, NULL);

	sfSprite* allSprites = sfSprite_create();
	sfRenderTexture* renderTexture = sfRenderTexture_create(1920, 1088, sfFalse); // coz 30 * BLOCK_SIZE & 17 * BLOCK_SIZE (64.f)
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


		sfRenderTexture_clear(renderTexture, sfBlue/*sfColor_fromRGB(6, 5, 13)*/);

		displayMap(renderTexture);
		displayPlayer(renderTexture);
		displayView(window);


		sfRenderTexture_display(renderTexture);

		allTextures = sfRenderTexture_getTexture(renderTexture);
		sfSprite_setTexture(allSprites, allTextures, sfFalse);

		sfRenderWindow_clear(window, sfBlue/*sfColor_fromRGB(6, 5, 13)*/);

		sfRenderWindow_drawSprite(window, allSprites, NULL);

		sfRenderWindow_display(window);

		if (sfKeyboard_isKeyPressed(sfKeyEscape) || sfMouse_isButtonPressed(sfMouseRight) /*&& sfWindow_hasFocus(window)*/) exit(EXIT_SUCCESS);

		
	}
}