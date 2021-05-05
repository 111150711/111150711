#pragma once
#include "CopyTab.h"
#include "CreateTab.h"
bool checkToRandom(int **&tab, int **&backTab, int size) {
	int can_put = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (tab[i][j] != backTab[i][j]) can_put = 1;
		}
	}
	return can_put;
}

//get point on random place in board
void randomOnBoard(int **&tab, int size) {

	if (checkPut(tab, size)) {
        //rate random
		int values[10] = { 2, 2, 2, 2, 4, 2, 2, 2, 2, 4 };
		int value = values[rand() % 10];

		int X = rand() % size;
		int Y = rand() % size;
		if (tab[X][Y] == 0) tab[X][Y] = value;
		else {
			while (tab[X][Y] != 0) {
				X = rand() % size;
				Y = rand() % size;
			}
			tab[X][Y] = value;
		}
	}
}

//move points in any direction
void rushTop(int **&tab, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] != 0) {
				for (int k = i; k > 0; --k) {
					if (tab[k - 1][j] == 0) {
						tab[k - 1][j] = tab[k][j];
						tab[k][j] = 0;
					}
				}
			}
		}
	}
}

void rushRight(int **&tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[i][j] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (tab[i][k + 1] == 0) {
						tab[i][k + 1] = tab[i][k];
						tab[i][k] = 0;
					}
				}
			}
		}
	}
}

void rushBot(int **&tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[j][i] != 0) {
				for (int k = j; k < size - 1; ++k) {
					if (tab[k + 1][i] == 0) {
						tab[k + 1][i] = tab[k][i];
						tab[k][i] = 0;
					}
				}
			}
		}
	}
}

void rushLeft(int **&tab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (tab[i][j] != 0) {
				for (int k = j; k > 0; --k) {
					if (tab[i][k - 1] == 0) {
						tab[i][k - 1] = tab[i][k];
						tab[i][k] = 0;
					}
				}
			}
		}
	}
}

void moveTop(int **&tab, int size, unsigned int &score) {
	rushTop(tab, size);

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (tab[i][j] != 0) {
				if (tab[i - 1][j] == tab[i][j]) {
					tab[i - 1][j]+= tab[i][j];
					score += tab[i - 1][j];
					tab[i][j] = 0;

				}
			}
		}
	}

	rushTop(tab, size);
}

void moveLeft(int **&tab, int size, unsigned int &score) {

	rushLeft(tab, size);

	for(int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			if (tab[i][j] != 0) {
				if (tab[i][j] == tab[i][j - 1]) {
					tab[i][j - 1] += tab[i][j];
					score += tab[i][j - 1];
					tab[i][j] = 0;
				}
			}
		}
	}

	rushLeft(tab, size);
}

void moveBot(int **&tab, int size, unsigned int &score) {
	rushBot(tab, size);

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[j][i] != 0) {
				if (tab[j][i] == tab[j + 1][i]) {
					tab[j + 1][i] += tab[j][i];
					score += tab[j + 1][i];
					tab[j][i] = 0;
				}
			}
		}
	}

	rushBot(tab, size);
}

void moveRight(int **&tab,int size, unsigned int &score) {

//check there is any move

	rushRight(tab, size);

	for (int i = 0; i < size; i++) {
		for (int j = size - 2; j >= 0; j--) {
			if (tab[i][j] != 0) {
				if (tab[i][j] == tab[i][j + 1]) {
					tab[i][j + 1] += tab[i][j];
					score += tab[i][j + 1];
					tab[i][j] = 0;
				}
			}
		}
	}

	rushRight(tab, size);
}

//choose direction od move
void move(SDL_Event event, int **&tab, int size, int **&backtab, unsigned int &score, unsigned int &backScore) {
	int **checkTab = createtab(size);
	int checkScore = backScore;
	copyTab(checkTab, backtab, size);

	copyTab(backtab, tab, size);
	backScore = score;


	if (event.key.keysym.sym == SDLK_UP) moveTop(tab, size, score);
	else if (event.key.keysym.sym == SDLK_DOWN) moveBot(tab, size, score);
	else if (event.key.keysym.sym == SDLK_LEFT) moveLeft(tab, size, score);
	else if (event.key.keysym.sym == SDLK_RIGHT) moveRight(tab, size, score);

	if (checkToRandom(tab, backtab, size)) {
		randomOnBoard(tab, size);
		Move++;
		/*
		chunk = Mix_LoadWAV("tie.ogg");
        if (!Mix_Playing(-1)) Mix_PlayChannel(-1, chunk, 0);
*/
	}
	else {
		copyTab(backtab, checkTab, size);
		backScore = checkScore;
		Back_Move = Move;

	}

	for (int i = 0; i < size; ++i)
		delete[] checkTab[i];
	delete[] checkTab;
}
