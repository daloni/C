#include <SDL/SDL.h>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>

int True = 1;
SDL_Surface* screenGeneral = NULL;
SDL_Surface* ball = NULL;
SDL_Surface* bar = NULL;
SDL_Surface* startButton = NULL;
SDL_Event event;
int widthScreen;
int heightScreen;

int game();

int main() {
	
	// Execute
	SDL_Init (SDL_INIT_EVERYTHING);
	TTF_Init();

	const SDL_VideoInfo* infoScreen = SDL_GetVideoInfo();

	widthScreen = infoScreen->current_w * 0.3;
	heightScreen = infoScreen->current_h * 0.8;
	
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
				game();
			}
		}
	}

	return 0;

}

int game() {
	SDL_Rect posicion_ball, posicion_barra;
	posicion_ball.x = 150;
	posicion_ball.y = 100;
	posicion_barra.x = widthScreen * 0.2;
	posicion_barra.y = heightScreen - heightScreen * 0.2;

	int x = 1, y = 1;
	int movImage = 5, moveBar = 5, moveBarLeftTrue = 0, moveBarRightTrue = 0;
	int delay = 15;
	int puntuacion = 0;

	ball = SDL_LoadBMP("./img/icon1.bmp");
	bar = SDL_LoadBMP("./img/barra.bmp");
	SDL_SetColorKey (ball, SDL_SRCCOLORKEY, SDL_MapRGB (ball->format, 0, 0, 0));
	SDL_SetColorKey (bar, SDL_SRCCOLORKEY, SDL_MapRGB (bar->format, 0, 0, 0));
	
	while (True == 1) {
		/* Movement of the ball */
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
		/* Change direction ball */
		if ((posicion_ball.y + ball->h > posicion_barra.y + 10 && 
		     posicion_ball.y < posicion_barra.y + bar->h && 
		     posicion_ball.x + ball->w > posicion_barra.x && 
		     posicion_ball.x < posicion_barra.x + bar->w && x == 1) ||
		    posicion_ball.x + ball->w > widthScreen) {
			x = 0;
		}
		if (posicion_ball.y + ball->h > posicion_barra.y &&
		    posicion_ball.y + ball->h < posicion_barra.y + 10 &&
		    posicion_ball.x + ball->w > posicion_barra.x && 
		    posicion_ball.x < posicion_barra.x + bar->w && y == 1) {
			y = 0;
			puntuacion++;
		}
		if ((posicion_ball.y + ball->h > posicion_barra.y + 10 && 
		     posicion_ball.y < posicion_barra.y + bar->h && 
		     posicion_ball.x + ball->w > posicion_barra.x && 
		     posicion_ball.x < posicion_barra.x + bar->w && x == 0) ||
		    posicion_ball.x < 0) {
			x = 1;
		}
		if (posicion_ball.y < 0) {
			y = 1;
		}
		/* Screen config */
		SDL_FillRect (screenGeneral, 0, SDL_MapRGB (screenGeneral->format, 42, 85, 224));
		SDL_BlitSurface(ball, NULL, screenGeneral, &posicion_ball);
		SDL_BlitSurface(bar, NULL, screenGeneral, &posicion_barra);
		SDL_Flip(screenGeneral);
		SDL_Delay(delay);
		/* Events */
		if(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN)) {
				SDL_FreeSurface(ball);
				SDL_FreeSurface(bar);
				return 0;
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
		if (moveBarLeftTrue == 1 && posicion_barra.x > 0) {
			posicion_barra.x = posicion_barra.x - moveBar;
		}
		if (moveBarRightTrue == 1 && posicion_barra.x + bar->w < widthScreen) {
			posicion_barra.x = posicion_barra.x + moveBar;
		}
		/* Game over */
		if (posicion_ball.y + ball->h > heightScreen) {
			printf("Game Over\n");
			return 0;
		}
	}
	return 1;
}
