#include <SDL/SDL.h>

int main() {

	SDL_Surface* screenGeneral = NULL;
	SDL_Surface* ball = NULL;
	SDL_Surface* bar = NULL;
	SDL_Event event;
	SDL_Rect posicion_ball, posicion_barra;
	posicion_ball.x = 150;
	posicion_ball.y = 100;
	posicion_barra.x = 250;
	posicion_barra.y = 750;

	int True = 1;
	int x = 1, y = 1;
	int movImage = 5, moveBar = 5, moveBarLeftTrue = 0, moveBarRightTrue = 0;
	int delay = 15;

	SDL_Init (SDL_INIT_EVERYTHING);

	ball = SDL_LoadBMP("./img/icon1.bmp");
	bar = SDL_LoadBMP("./img/barra.bmp");
	SDL_WM_SetIcon(SDL_LoadBMP("./img/icon.bmp"), NULL);
	screenGeneral = SDL_SetVideoMode(600, 800, 32, SDL_SWSURFACE);
	
	while (True == 1) {
		if (x == 1 && y == 1) {
			posicion_ball.x = posicion_ball.x + movImage;
			posicion_ball.y = posicion_ball.y + movImage;
		} else if (x == 0 && y == 1) {
			posicion_ball.x = posicion_ball.x - movImage;
			posicion_ball.y = posicion_ball.y + movImage;
		} else if (x == 1 && y == 0) {
			posicion_ball.x = posicion_ball.x + movImage;
			posicion_ball.y = posicion_ball.y - movImage;
		} else {
			posicion_ball.x = posicion_ball.x - movImage;
			posicion_ball.y = posicion_ball.y - movImage;
		}
		
		if (posicion_ball.x + ball->w > 600) {
			x = 0;
		}
		if (posicion_ball.y + ball->h > posicion_barra.y && 
		    posicion_ball.x + ball->w > posicion_barra.x && 
		    posicion_ball.x < posicion_barra.x + bar->w) {
			y = 0;
		}
		if (posicion_ball.x < 0) {
			x = 1;
		}
		if (posicion_ball.y < 0) {
			y = 1;
		}
		
		SDL_FillRect (screenGeneral, 0, SDL_MapRGB (screenGeneral->format, 0, 0, 0));
		SDL_BlitSurface(ball, NULL, screenGeneral, &posicion_ball);
		SDL_BlitSurface(bar, NULL, screenGeneral, &posicion_barra);
		SDL_Flip(screenGeneral);
		SDL_Delay(delay);
		
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				SDL_FreeSurface(ball);
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
		if (moveBarLeftTrue == 1 && posicion_barra.x > 0) {
			posicion_barra.x = posicion_barra.x - moveBar;
		}
		if (moveBarRightTrue == 1 && posicion_barra.x + bar->w < 600) {
			posicion_barra.x = posicion_barra.x + moveBar;
		}
		
		if (posicion_ball.y + ball->h > 800) {
			printf("Game Over\n");
			SDL_Quit();
			return 0;
		}
	}

	return 0;

}