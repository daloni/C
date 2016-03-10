#include "game.h"

SDL_Surface* startButton = NULL;
SDL_Event event;

int main() {
	
	Screen sc;

	// Execute
	SDL_Init (SDL_INIT_EVERYTHING);
	TTF_Init();

	const SDL_VideoInfo* infoScreen = SDL_GetVideoInfo();

	sc.widthScreen = infoScreen->current_w * 0.3;
	sc.heightScreen = infoScreen->current_h * 0.8;
	
	// Score
	int score, i, a, e, intBestScore;
	char charFileScore[20], charBestScore[20];
	FILE  *f;
	f = fopen("score.txt", "a+");

	// Variables
	int buttonPositionX, buttonPositionY;
	SDL_Rect startButtonPosition, textStartPosition;
	startButtonPosition.x = sc.widthScreen * 0.35;
	startButtonPosition.y = sc.heightScreen * 0.4;
	startButton = SDL_LoadBMP("./img/start_button.bmp");
	SDL_SetColorKey (startButton, SDL_SRCCOLORKEY, SDL_MapRGB (startButton->format, 0, 0, 0));

	textStartPosition.x = startButtonPosition.x + startButton->w * 0.3;
	textStartPosition.y = startButtonPosition.y + startButton->h + 20;

	
	// Config	
	SDL_WM_SetIcon(SDL_LoadBMP("./img/icon.bmp"), NULL);
	sc.screenGeneral = SDL_SetVideoMode(sc.widthScreen, sc.heightScreen, 32, /*SDL_SWSURFACE*/ SDL_RESIZABLE);

	SDL_FillRect(sc.screenGeneral, 0, SDL_MapRGB (sc.screenGeneral->format, 42, 85, 224));

	TTF_Font* font = TTF_OpenFont("./fonts/arial.ttf", 12);
	SDL_Surface *text;
	SDL_Color text_color = {0, 0, 0};

	// Write text to surface
	text = TTF_RenderText_Solid(font, "Presiona enter", text_color);

	SDL_BlitSurface(startButton, NULL, sc.screenGeneral, &startButtonPosition);
	SDL_BlitSurface(text, NULL, sc.screenGeneral, &textStartPosition);
	
	while (1) {
		/* On click Quit */
		SDL_FillRect(sc.screenGeneral, 0, SDL_MapRGB (sc.screenGeneral->format, 42, 85, 224));
		SDL_BlitSurface(startButton, NULL, sc.screenGeneral, &startButtonPosition);
		SDL_BlitSurface(text, NULL, sc.screenGeneral, &textStartPosition);
		SDL_Flip(sc.screenGeneral);
		while(SDL_PollEvent(&event)) {
			buttonPositionX = event.motion.x;
			buttonPositionY = event.motion.y;

			if (event.type == SDL_QUIT || (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN)) {
				SDL_Quit();
				SDL_FreeSurface(startButton);
				return 0;
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
				score = game(sc);
				fprintf(f, "Dani %i\n", score);
				fclose(f);
			}
		}
	}
	return 0;
}