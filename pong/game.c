#include "game.h"

SDL_Surface* ball = NULL;
SDL_Surface* bar = NULL;
SDL_Event event;

int game(SDL_Surface* screenGeneral, int widthScreen, int heightScreen) {
	
	SDL_Rect position_ball, position_barra, position_score;
	position_ball.x = 150;
	position_ball.y = 100;
	position_barra.x = widthScreen * 0.2;
	position_barra.y = heightScreen * 0.9;
	position_score.x = widthScreen * 0.8;
	position_score.y = heightScreen * 0.1;

	int x = 1, y = 1;
	int movImage = 5, moveBar = 5, moveBarLeftTrue = 0, moveBarRightTrue = 0;
	int delay = 15;
	int countScore = 0;
	char scoreChar[20];

	ball = SDL_LoadBMP("./img/icon1.bmp");
	bar = SDL_LoadBMP("./img/barra.bmp");
	SDL_SetColorKey (ball, SDL_SRCCOLORKEY, SDL_MapRGB (ball->format, 0, 0, 0));
	SDL_SetColorKey (bar, SDL_SRCCOLORKEY, SDL_MapRGB (bar->format, 0, 0, 0));

	/* Score */
	TTF_Font* font = TTF_OpenFont("./fonts/arial.ttf", 12);
	SDL_Surface *score;
	SDL_Color text_color = {0, 0, 0};
	
	while (1) {
		/* Movement of the ball */
		//printf("%i > %i\n", position_barra.x, bar->h);
		if (x == 1 && y == 1) {
			position_ball.x = position_ball.x + movImage;
			position_ball.y = position_ball.y + movImage;
		} else if (x == 0 && y == 1) {
			position_ball.x = position_ball.x - movImage;
			position_ball.y = position_ball.y + movImage;
		} else if (x == 1 && y == 0) {
			position_ball.x = position_ball.x + movImage;
			position_ball.y = position_ball.y - movImage;
		} else {
			position_ball.x = position_ball.x - movImage;
			position_ball.y = position_ball.y - movImage;
		}
		/* Change direction ball */
		if ((position_ball.y + ball->h > position_barra.y + 6 &&
		     position_ball.y < position_barra.y + bar->h &&
		     position_ball.x + ball->w > position_barra.x &&
		     position_ball.x < position_barra.x + bar->w/2 && x == 1) ||
		    position_ball.x + ball->w > widthScreen) {
			x = 0;
		}
		if (position_ball.y + ball->h > position_barra.y &&
		    position_ball.y + ball->h < position_barra.y + 10 &&
		    position_ball.x + ball->w > position_barra.x && 
		    position_ball.x < position_barra.x + bar->w && y == 1) {
			y = 0;
			if (countScore < 999) {
				countScore++;
			}
		}
		if ((position_ball.y + ball->h > position_barra.y + 6 &&
		     position_ball.y < position_barra.y + bar->h
		     && position_ball.x + ball->w > position_barra.x + bar->w/2 &&
		     position_ball.x < position_barra.x + bar->w && x == 0) ||
		    position_ball.x < 0) {
			x = 1;
		}
		if (position_ball.y < 0) {
			y = 1;
		}
		/* Score */
		sprintf(scoreChar, "Puntuacion: %i", countScore);
		score = TTF_RenderText_Solid(font, scoreChar, text_color);
		/* Screen config */
		SDL_FillRect (screenGeneral, 0, SDL_MapRGB (screenGeneral->format, 42, 85, 224));
		SDL_BlitSurface(ball, NULL, screenGeneral, &position_ball);
		SDL_BlitSurface(bar, NULL, screenGeneral, &position_barra);
		SDL_BlitSurface(score, NULL, screenGeneral, &position_score);
		SDL_Flip(screenGeneral);
		SDL_Delay(delay);
		/* Events */
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN)) {
				SDL_FreeSurface(ball);
				SDL_FreeSurface(bar);
				return countScore;
			}
			/* Event of the keys */
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
		/* Movement of the bar */
		if (moveBarLeftTrue == 1 && position_barra.x > 0) {
			position_barra.x = position_barra.x - moveBar;
		}
		if (moveBarRightTrue == 1 && position_barra.x + bar->w < widthScreen) {
			position_barra.x = position_barra.x + moveBar;
		}
		/* Game over */
		if (position_ball.y + ball->h > heightScreen) {
			printf("Game Over\n");
			return countScore;
		}
	}
}