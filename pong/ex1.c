#include <SDL/SDL.h>

int main() {

	SDL_Surface* screenGeneral = NULL;
	SDL_Surface* image = NULL;
	SDL_Surface* bar = NULL;
	SDL_Event event;
	SDL_Rect posicion_image, posicion_barra;
	posicion_image.x = 150;
	posicion_image.y = 100;
	posicion_barra.x = 250;
	posicion_barra.y = 750;

	int True = 1;
	int x = 1, y = 1;
	int movImage = 5, moveBar = 5, moveBarLeftTrue = 0, moveBarRightTrue = 0;

	SDL_Init (SDL_INIT_EVERYTHING);

	image = SDL_LoadBMP("./icon/icon1.bmp");
	bar = SDL_LoadBMP("./icon/barra.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("./icon/icon.bmp"), NULL);
	screenGeneral = SDL_SetVideoMode(600, 800, 32, SDL_SWSURFACE);


	
	while (True == 1) {
		if (x == 1 && y == 1) {
			posicion_image.x = posicion_image.x + movImage;
			posicion_image.y = posicion_image.y + movImage;
		} else if (x == 0 && y == 1) {
			posicion_image.x = posicion_image.x - movImage;
			posicion_image.y = posicion_image.y + movImage;
		} else if (x == 1 && y == 0) {
			posicion_image.x = posicion_image.x + movImage;
			posicion_image.y = posicion_image.y - movImage;
		} else {
			posicion_image.x = posicion_image.x - movImage;
			posicion_image.y = posicion_image.y - movImage;
		}

		if (posicion_image.x + 48 > 600 || ) {
			x = 0;
		}
		if (posicion_image.y + 48 > 800) {
			y = 0;
		}
		if (posicion_image.x < 0) {
			x = 1;
		}
		if (posicion_image.y < 0) {
			y = 1;
		}
		
		SDL_FillRect (screenGeneral, 0, SDL_MapRGB (screenGeneral->format, 0, 0, 0));
		SDL_BlitSurface(image, NULL, screenGeneral, &posicion_image);
		SDL_BlitSurface(bar, NULL, screenGeneral, &posicion_barra);
		SDL_Flip(screenGeneral);
		SDL_Delay(15);
		
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_FreeSurface(image);
				SDL_Quit();
				return 0;
			}
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					moveBarLeftTrue = 1;
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					moveBarRightTrue = 1;
				}
			} 
			if (event.type == SDL_KEYUP) {
				if (event.key.keysym.sym == SDLK_LEFT) {
					moveBarLeftTrue = 0;
				}
				if (event.key.keysym.sym == SDLK_RIGHT) {
					moveBarRightTrue = 0;
				}
			}
			
		}
		if (moveBarLeftTrue == 1) {
			posicion_barra.x = posicion_barra.x - moveBar;
		}
		if (moveBarRightTrue == 1) {
			posicion_barra.x = posicion_barra.x + moveBar;
		}
		
		
	}

	return 0;

}