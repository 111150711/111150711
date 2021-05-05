#include "Move.cpp"

bool checkToRandom(int **&tab, int **&backTab, int size);
void randomOnBoard(int **&tab, int size);
void rushTop(int **&tab, int size);
void rushRight(int **&tab, int size);
void rushBot(int **&tab, int size);
void rushLeft(int **&tab, int size);
void moveTop(int **&tab, int size, unsigned int &score);
void moveLeft(int **&tab, int size, unsigned int &score);
void moveBot(int **&tab, int size, unsigned int &score);
void moveRight(int **&tab,int size, unsigned int &score);
void move(SDL_Event event, int **&tab, int size, int **&backtab, unsigned int &score, unsigned int &backScore);
