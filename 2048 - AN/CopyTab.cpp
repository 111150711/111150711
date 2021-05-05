#pragma once
//copy one array to another
void copyTab(int **&tab,int **&backtab, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) tab[i][j] = backtab[i][j];
	}
}
