#include <cmath>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Init.h"
#include "CreateTab.h"
#include "CopyTab.h"
#include "DrawString.h"
#include "showText.h"
#include "check.h"
#include "Draw.h"
#include "Move.h"
#include "Score.h"

int main(int argc, char **argv) {
    int HighScore ;
    std::ifstream file;
    file.open("HighScore.txt");
    file >> HighScore;
    if (HighScore < 0) HighScore = 0;

    srand(time(NULL)); //free random
    playerScore *winnerList;

    if (Init() != 0) return 1;
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,&window, &renderer);
	if (WinAndRen(rc) != 0) return 1;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	//choose color for renderer
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //black

	SDL_SetWindowTitle(window, "2048 Pro Version");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH, SCREEN_HEIGHT);

	charset = SDL_LoadBMP("Image/cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};
	SDL_SetColorKey(charset, true, 0x000000);

	char text[128];

    const int Yellow = SDL_MapRGB(screen->format, 255, 255, 204);
	const int Orange = SDL_MapRGB(screen->format, 255, 179, 102);
	const int Dark = SDL_MapRGB(screen->format, 57, 140, 119);
	const int Light = SDL_MapRGB(screen-> format, 251,248,239);
	SDL_Color Orange_txt = {255, 179, 102};
    SDL_Color Yellow_txt = {255, 255, 204};

	tab = createtab(size);
	backtab = createtab(size);
	copyTab(tab, backtab, size);
	winnerList = openFile(fileSize);

    int Indent_left, Indent_top ;

    bool Music = 1;
	while(!quit) {
        //play music
        music = Mix_LoadMUS("Audio/background.mp3");
        if (music == NULL)
        {
            printf("%s", Mix_GetError());
        }
        if (!Mix_PlayingMusic())
            Mix_PlayMusic(music, -1);


		//SHOW START WINDOW TO CHOOSE SIZE FROM 3 TO 10
		if (!getStart) {

			if (size >= 8) size = 8;
			if (size <= 3) size = 3;

			SDL_FillRect(screen, NULL, Yellow);
			Indent_left = 10;
			Indent_top =10;
            DrawRectangle(screen, Indent_left, Indent_top, SCREEN_WIDTH - 2*Indent_left, 40,Yellow, Orange);
			//cần có kí tự mũi tên
            sprintf(text, "Choose size of map: \030 - Bigger, \031 - Smaller, Enter - accept");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			DrawRectangle(screen, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 36, 200, 36, Yellow, Orange);
            std::string Text;

			switch(size){
                case 3:{
                    Text = "Tiny (3x3)";

                    break;
                }
                case 4:{
                    Text =  "Classic (4x4)";
                    break;
                }
                case 5:{
                    Text =  "Big (5x5)";
                    break;
                }
                case 6:{
                    Text =  "Bigger (6x6)";
                    break;
                }
                case 7:{
                    Text =  "Huge (7x7)";
                    break;
                }
                case 8:{
                    Text =  "Huger (8x8)";
                    break;
                }
			}

			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
				    if (event.key.keysym.sym == SDLK_m ) {
                        if (Music == 1 ){
                            Mix_PauseMusic();
                            Music = 0;
                        }
                        else {
                            Mix_ResumeMusic();
                            Music = 1;
                        }
				    }

					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
                    else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_RIGHT) size++;
                    else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_LEFT) size--;
                    else if (event.key.keysym.sym == SDLK_RETURN) { //enter

						getStart = 1;
						tab = createtab(size);
						backtab = createtab(size);
						copyTab(tab, backtab, size);
						t1 = SDL_GetTicks();
						backScore = 0;
						score = 0;
						worldTime = 0;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};


			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);

			//draw text
			srcRect.x = 0;
            srcRect.y = 0;
            desRect.x = 216;
            desRect.y = 85;
			showText(renderer, "2048",100,Orange_txt,srcRect, desRect);

			desRect.x = SCREEN_WIDTH/2  -  Text.size() * 4; // left
            desRect.y = SCREEN_HEIGHT / 2 - 26; // top

			showText(renderer, Text,20,Yellow_txt,srcRect, desRect);


			//render

			SDL_RenderPresent(renderer);

		}
		//SHOW GAME WINDOW
		else if(getStart && !checkLose(tab, size) && !checkWin(tab, size)){

			//TIME COUNING
			t2 = SDL_GetTicks();
			delta = (t2 - t1) * 0.001;
			t1 = t2;
			worldTime += delta;
			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};

			SDL_FillRect(screen, NULL, Light);

			DrawBoard(renderer,screen, tab, size, Yellow, Orange);

			DrawResults(renderer, score, Move,HighScore);
			SDL_RenderPresent(renderer);

			//info text
            DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, Yellow, Orange);
			sprintf(text, "time = %.1lf s  %.0lf frames / s", worldTime, fps);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			sprintf(text, "Esc - Exit, \032 \030 \031 \033  - Move, u - Back move, n - New game, r - Rank");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			//SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			//SDL_RenderPresent(renderer);

			while(SDL_PollEvent(&event)) {
				switch(event.type) {
					case SDL_KEYDOWN:
					    if (event.key.keysym.sym == SDLK_m ) {
                            if (Music == 1 ){
                                Mix_PauseMusic();
                                Music = 0;
                            }
                            else {
                                Mix_ResumeMusic();
                                Music = 1;
                            }
                        }
                        if (event.key.keysym.sym == SDLK_s)
                            saveToFile(score, worldTime, size);
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						else if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN ||
							event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_RIGHT){
                                move(event, tab, size, backtab, score, backScore);

							}
						else if (event.key.keysym.sym == SDLK_u) {
							copyTab(tab, backtab, size);
							score = backScore;
							Move = Back_Move;
						}
						else if (event.key.keysym.sym == SDLK_n) {
							for (int i = 0; i < size; ++i)
								delete[] tab[i];
							delete[] tab;

							for (int i = 0; i < size; ++i)
								delete[] backtab[i];
							delete[] backtab;
							getStart = 0;
						}
						else if (event.key.keysym.sym == SDLK_r) {	//SHOW RANKING WINDOW

							bool show_ranking = 0;
							int amountBoard = 0;
							int startShow = 0;
							int limit = 10;
							for (int i = 0; i < fileSize; i++) if (size == winnerList[i].endSize) amountBoard++;
							playerScore *sizeRanking = createRanking(winnerList, amountBoard, size, fileSize);
							while (!show_ranking) {

								SDL_FillRect(screen, NULL, Yellow);
								DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, Yellow, Orange);
								sprintf(text, "Winner list for %dx%d", size, size);
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
								sprintf(text, "esc -  go back, press t to sort by time and p to sort by points");
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);


								//set start of ranking
								if (startShow <= 0) startShow = 0;
								if (startShow >= amountBoard - 10) startShow = amountBoard - 10;
								if (amountBoard <= 10) {
									startShow = 0;
									limit = amountBoard;
								}

								//check there is winner list
								if (fileSize == 0 || limit == 0) {
									sprintf(text, "Winner list in empty");
									DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 + 16, text, charset);
								}

								int placeShow = 0;
								for (int i = startShow; placeShow < limit; i++) {
									DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 190 + placeShow * 40, 400, 40, Yellow,Orange);
									sprintf(text, "%d. Your time: %.1lfs Your score: %d",startShow + placeShow + 1, sizeRanking[i].endTime, sizeRanking[i].endScore);
									DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 200 + 26 + placeShow * 40, text, charset);
									placeShow++;
								}

								while (SDL_PollEvent(&event)) {
									switch (event.type) {
									case SDL_KEYDOWN:
										if (event.key.keysym.sym == SDLK_ESCAPE) show_ranking = 1;
										if (event.key.keysym.sym == SDLK_t) sortByTime(sizeRanking, amountBoard);
										if (event.key.keysym.sym == SDLK_p) sortByScore(sizeRanking, amountBoard);
										else if (event.key.keysym.sym == SDLK_UP) startShow++;
										else if (event.key.keysym.sym == SDLK_DOWN) startShow--;

										break;
									case SDL_QUIT:
										quit = 1;
										show_ranking = 1;
										break;
									};
								};

								SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
								SDL_RenderCopy(renderer, scrtex, NULL, NULL);
								SDL_RenderPresent(renderer);
							}
							delete[] sizeRanking;
						}
						break;
					case SDL_KEYUP:
						etiSpeed = 1.0;
						break;
					case SDL_QUIT:
						quit = 1;
						break;
				};
			};
			frames++;
		}
		//CHECK IF PLAYER LOSE AND SHOW ENDCSREEN
		else if (checkLose(tab, size)) {
            chunk = Mix_LoadWAV("Audio/you_lose.ogg");
            if (chunk == NULL)
            {
                printf("%s", Mix_GetError());
                return -1;
            }
            if (!Mix_Playing(-1)) Mix_PlayChannel(-1, chunk, 0);
			double endTime = worldTime;

			while (!quit) {
				SDL_FillRect(screen, NULL, Yellow);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, Yellow, Orange);
				sprintf(text, "You Lose: s - to save your time, esc -  to quit");

				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

				DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, Yellow, Orange);
				sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, score);
				DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						if (event.key.keysym.sym == SDLK_s) {
							saveToFile(score, endTime, size);


                            while (!quit) {

                                SDL_FillRect(screen, NULL, Yellow);
                                DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, Yellow, Orange);
                                sprintf(text, "Score saved!");
                                DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
                                sprintf(text, "esc -  close game");
                                DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

                                while (SDL_PollEvent(&event)) {
                                    switch (event.type) {
                                    case SDL_KEYDOWN:
                                        if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;

                                        break;
                                    case SDL_QUIT:
                                        quit = 1;
                                        break;
                                    };
                                };

                                SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
                                SDL_RenderCopy(renderer, scrtex, NULL, NULL);
                                SDL_RenderPresent(renderer);
                            }
                        }
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}


		}
		else if (checkWin(tab, size)) {
            chunk = Mix_LoadWAV("Audio/you_win.ogg");
            if (chunk == NULL)
            {
                printf("%s", Mix_GetError());
                return -1;
            }
            if (!Mix_Playing(-1)) Mix_PlayChannel(-1, chunk, 0);
			double endTime = worldTime;
			while (!quit) {
				SDL_FillRect(screen, NULL, Yellow);
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, Yellow, Orange);
				sprintf(text, "You Win: s - to save your time, esc -  to quit");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

				DrawRectangle(screen, SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 36, 400, 36, Yellow, Orange);
				sprintf(text, "Your time: %.1lfs  Your score: %u", endTime, score);
				DrawString(screen, SCREEN_WIDTH / 2 - strlen(text) * 4, SCREEN_HEIGHT / 2 - 20, text, charset);


				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						if (event.key.keysym.sym == SDLK_s) {
							saveToFile(score, endTime, size);


							while (!quit) {

								SDL_FillRect(screen, NULL, Yellow);
								DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, Yellow, Orange);
								sprintf(text, "Score saved!");
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
								sprintf(text, "esc -  close game");
								DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

								while (SDL_PollEvent(&event)) {
									switch (event.type) {
									case SDL_KEYDOWN:
										if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;

										break;
									case SDL_QUIT:
										quit = 1;
										break;
									};
								};

								SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
								SDL_RenderCopy(renderer, scrtex, NULL, NULL);
								SDL_RenderPresent(renderer);
							}
						}
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				};

				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
		}
	};

	//freeing all surfaces and memory
	for (int i = 0; i < size; ++i)
		delete[] tab[i];
	delete[] tab;

	for (int i = 0; i < size; ++i)
		delete[] backtab[i];
	delete[] backtab;

	delete[] winnerList;

	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
	};
