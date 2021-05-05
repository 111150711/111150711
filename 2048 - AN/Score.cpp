struct playerScore{
	int endScore;
	double endTime;
	int endSize;
};

void DrawResults(SDL_Renderer *renderer, unsigned int score, int Move, int HighScore) {
	std::string Text = "score: " +std::to_string(score);
	SDL_Rect srcRect;
    SDL_Rect desRect;
    srcRect.x = 0;
    srcRect.y = 0;
	desRect.x = BOARD_Y + BOARD_WIDTH + 20;
    desRect.y =  BOARD_X + 10;
    SDL_Color Black_txt = {102, 102, 153};
    showText(renderer, Text,28 ,Black_txt,srcRect, desRect);
    if ( Move == 0 || Move == 1)Text =  std::to_string(Move) +" move";
    else Text =  std::to_string(Move) +" moves";
    desRect.y =  BOARD_X + 383;
	showText(renderer, Text,15 ,Black_txt,srcRect, desRect);

	if (score > HighScore) {
        HighScore = score;
        std::ofstream File("HighScore.txt");
        File << HighScore;
	}
	desRect.y =  BOARD_X + 60;
	Text = "HighScore: " +std::to_string(HighScore);
	showText(renderer, Text,30 ,Black_txt,srcRect, desRect);

}

//bubble sort
void sortByScore(playerScore *&tab, int size) {
	playerScore helper;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (tab[j].endScore > tab[j + 1].endScore) {
				helper = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = helper;
			}
		}
	}

	for (int i = 0; i < size / 2; i++) {
		helper = tab[i];
		tab[i] = tab[size - i - 1];
		tab[size - i - 1] = helper;
	}
}

void sortByTime(playerScore *&tab, int size) {
	playerScore helper;
	for (int i = 0; i < size - 1; i++) {
		for (int j = 0; j < size - 1 - i; j++) {
			if (tab[j].endTime > tab[j + 1].endTime) {
				helper = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = helper;
			}
		}
	}
}

//create list of score for board size
playerScore *createRanking(playerScore *tab, int amount, int size, int fileSize) {
	playerScore *ranking = new playerScore[amount];
	int j = 0;
	for (int i = 0; i < fileSize; i++) {
		if (tab[i].endSize == size) {
			ranking[j].endScore = tab[i].endScore;
			ranking[j].endTime = tab[i].endTime;
			ranking[j].endSize = tab[i].endSize;
			j++;
		}
	}
	return ranking;
}


//create whole list of scores
playerScore *openFile(int &lines){
	FILE *fileList = fopen("winnerList.txt", "r");
	int ch = 0;

	if (fileList == NULL)
	{
		return 0;
	}

	while (!feof(fileList))
	{
		ch = fgetc(fileList);
		if (ch == '\n')
		{
			lines++;
		}
	}

	playerScore *list = new playerScore [lines];
	fseek(fileList, 0, SEEK_SET);
	for (int i = 0; i < lines; i++) {
		fscanf(fileList, "%d %lf %d", &list[i].endScore, &list[i].endTime, &list[i].endSize);
	}
	fclose(fileList);

	return list;
}

void saveToFile(int score, double time, int size) {
	FILE *fileList = fopen("winnerList.txt", "a");
	fprintf(fileList, "%u %.1lf %d\n", score, time, size);

	fclose(fileList);
}



