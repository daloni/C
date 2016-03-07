#include <SDL/SDL.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string.h>

int True = 1;
SDL_Surface* screenGeneral = NULL;
SDL_Surface* ball = NULL;
SDL_Surface* bar = NULL;
SDL_Surface* startButton = NULL;
SDL_Event event;
int widthScreen;
int heightScreen;

int main() {
	
	// Execute
	SDL_Init (SDL_INIT_EVERYTHING);
	TTF_Init();

	const SDL_VideoInfo* infoScreen = SDL_GetVideoInfo();

	widthScreen = infoScreen->current_w * 0.3;
	heightScreen = infoScreen->current_h * 0.8;
	
	// Score
	int score, i, a, e, intBestScore;
	char charFileScore[20], charBestScore[20];
	FILE  *f;
	f = fopen("score.txt", "a+");

	// Variables
	int buttonPositionX, buttonPositionY;
	SDL_Rect startButtonPosition, textStartPosition;
	startButtonPosition.x = widthScreen * 0.35;
	startButtonPosition.y = heightScreen * 0.4;
	startButton = SDL_LoadBMP("./img/start_button.bmp");
	SDL_SetColorKey (startButton, SDL_SRCCOLORKEY, SDL_MapRGB (startButton->format, 0, 0, 0));

	textStartPosition.x = startButtonPosition.x + startButton->w * 0.3;
	textStartPosition.y = startButtonPosition.y + startButton->h + 20;

	
	// Config	
	SDL_WM_SetIcon(SDL_LoadBMP("./img/icon.bmp"), NULL);
	screenGeneral = SDL_SetVideoMode(widthScreen, heightScreen, 32, /*SDL_SWSURFACE*/ SDL_RESIZABLE);

	SDL_FillRect(screenGeneral, 0, SDL_MapRGB (screenGeneral->format, 42, 85, 224));

	TTF_Font* font = TTF_OpenFont("./fonts/arial.ttf", 12);
	SDL_Surface *text;
	SDL_Color text_color = {0, 0, 0};

	// Write text to surface
	text = TTF_RenderText_Solid(font, "Presiona enter", text_color);

	SDL_BlitSurface(startButton, NULL, screenGeneral, &startButtonPosition);
	SDL_BlitSurface(text, NULL, screenGeneral, &textStartPosition);
	
	while (True == 1) {
		/* On click Quit */
		SDL_FillRect(screenGeneral, 0, SDL_MapRGB (screenGeneral->format, 42, 85, 224));
		SDL_BlitSurface(startButton, NULL, screenGeneral, &startButtonPosition);
		SDL_BlitSurface(text, NULL, screenGeneral, &textStartPosition);
		SDL_Flip(screenGeneral);
		while(SDL_PollEvent(&event)) {
			buttonPositionX = event.motion.x;
			buttonPositionY = event.motion.y;

			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN)) {
				SDL_Quit();
				SDL_FreeSurface(startButton);
				True = 0;
			}

			if((buttonPositionX > startButtonPosition.x && buttonPositionX < startButtonPosition.x + startButton->w &&
			   buttonPositionY > startButtonPosition.y && buttonPositionY < startButtonPosition.y + startButton->h &&
			   event.button.button == SDL_BUTTON_LEFT) || event.key.keysym.sym == SDLK_RETURN) {
				f = fopen("score.txt", "a+");
				while (fgets(charFileScore, 20, f)!=NULL) {
					a = strlen(charFileScore);
					e = 0;
					while (charFileScore[a] != ' ') {
						a--;
						e++;
					}
					for (i = 0; i < e-1; i++) {
						charBestScore[i] = charFileScore[e + i];
					}
					//printf("%s\n", charBestScore);
				}
				score = game();
				fprintf(f, "Dani %i\n", score);
				fclose(f);
			}
		}
	}
	return 0;
}

int game() {
	
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
	
	while (True == 1) {
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