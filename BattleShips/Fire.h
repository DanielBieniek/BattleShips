#pragma once

int shoot(int x, int y, int board[10][10]) {
	y -= 1; x -= 1; //for user-friendly experience. the board has coordinates 1-10, but arrays have indexes 0-9
	if (x < 0 || x >= 10 || y < 0 || y >= 10) { //if hit outside the board
		color(1);
		printf_s("\nWork on your aim and hit the board next time!\n\n");
		color(0);
		return 1;
	} else if (board[x][y] == 0) { //if water hit
		board[x][y] = 3;
	} else if (board[x][y] == 1) { //if ship hit
		board[x][y] = 2;
	} else if (board[x][y] == 2 || board[x][y] == 3) { //if place was already hit
		color(1);
		printf_s("\nYou already hit this place, don't waste your ammo!\n\n");
		color(0);
		return 1;
	} else {
		color(1);
		printf_s("\nYou couldn't possibly get here without cheating.\n\n");
		color(0);
		return 1;
	}
	return 0;
}

void scanFireLocation(int board[10][10]) {
	char x[3], y[3];
	int errors = 0;
	do {
		printf_s("Where do you want to hit?\n");
		printf_s("Give me X: ");
		scanf_s(" %s", &x, 3);
		printf_s("Give me Y: ");
		scanf_s(" %s", &y, 3);
		errors = shoot(validateInput(x,1), validateInput(y,1), board);
	} while (errors);
	system("cls");
}