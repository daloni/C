#include <SDL/SDL.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>

typedef struct Screen {
	SDL_Surface* screenGeneral;
	int widthScreen;
	int heightScreen;
} Screen;


int game(Screen sc);