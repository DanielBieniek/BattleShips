#pragma once

void saveGame(int roundNumber, int board1[10][10], int board2[10][10]) {
	FILE *file;
	fopen_s(&file, "autoSave.txt", "w");
	if (file != NULL) {
		fprintf(file, "%d\n", roundNumber); //puts round number in the first row
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) { //the next 100 rows in a text file are the contained in board1
				fprintf(file, "%d", board1[i][j]);
				fprintf(file, "\n");
			}
		}
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) { //the last 100 rows in a text file are the contained in board2
				fprintf(file, "%d", board2[i][j]);
				if (!(i == 9 && j == 9)) fprintf(file, "\n"); //prevents the file from having last line empty. it will be easier to loadGame
			}
		}
	}
	fclose(file);
}

loaded loadGame() {
	struct loaded load;
	int i = -1, x, y; //start i with -1, for easier calculation. first row is roundNumber, and the rest are coordinates of 2d array of board
	FILE *file;
	if (!fopen_s(&file, "autoSave.txt", "r")) {
		while (!feof(file)) {
			if (i == -1) {
				fscanf_s(file, " %d", &load.roundNumber);
				i++;
			} else if (i >= 0 && i <= 99) {
				x = i / 10;
				y = i % 10;
				fscanf_s(file, " %d", &load.board1[x][y]); //write data into board1
				i++;
			} else if (i >= 100 && i <= 199) {
				x = (i-100) / 10;
				y = (i - 100) % 10;
				fscanf_s(file, " %d", &load.board2[x][y]); //write data into board2
				i++;
			}
		}
		fclose(file);
	} else {
		load.roundNumber = -3; //if the file couldn't be open set roundnumber to -3, it will be sent to menu and it will give main() the info about an error
	}
	return load; //returns a structure. the only way I know how to return 3 variables (board1,board2,roundNumber) from one function.
}