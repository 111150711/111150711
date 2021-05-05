#include "Score.cpp"

void DrawResults(SDL_Renderer *renderer, unsigned int score, int Move, int HighScore);
void sortByScore(playerScore *&tab, int size);
void sortByTime(playerScore *&tab, int size);
playerScore *createRanking(playerScore *tab, int amount, int size, int fileSize);
void saveToFile(int score, double time, int size);
playerScore *openFile(int &lines);
