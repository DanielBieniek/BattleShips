// placingShips.h is a header created to place ships,
// after giving x,y coordinates of most top-left cell,
// direction (0 - horizontal, 1 - vertical),
// 2d array with a board

#pragma once

//s - size, x - vertical coordinate, y - horizontal coordinate, d - direction, board[10][10] - current state of the board
int placeShip(int s, int x, int y, int d, int board[10][10]) {
	y -= 1; x -= 1; //for user-friendly experience. the board has coordinates 1-10, but arrays have indexes 0-9
	//ERROR CHECKING
	if (d != 0 && d != 1) {
		color(1);
		printf_s("Incorrect direction.\n");
		color(0);
		return 1;
	}
	if ((x<0) || (y<0) || (d == 0 && y > 10 - s) || (d == 1 && x > 10 - s)) {
		color(1);
		printf_s("The ship is out of bands!\n");
		color(0);
		return 1;
	}
	for (int i = 0;i < 10;i++) { //check if placed ship will overlap another ship
		for (int j = 0;j < 10;j++) {
			if ((d == 0 && i == x && j >= y && j < y + s) || (d == 1 && j == y && i >= x && i < x + s)) { //handles both directions: vertical and horizontal and for all ship sizes
				if (board[i][j] == 1) {
					color(1);
					printf_s("Ships overlap!\n");
					color(0);
					return 1;
				}
			}
		}
	}
	for (int i = 0;i < 10;i++) { //place '1's in the board at the ship part location
		for (int j = 0;j < 10;j++) {
			if ((d == 0 && i == x && j >= y && j < y + s) || (d == 1 && j == y && i >= x && i < x + s)) { //handles both directions: vertical and horizontal and for all ship sizes
				board[i][j] = 1;
			}
		}
	}
	return 0;
}

void scanShipLocation(int board[10][10]) {
	char x5[3], y5[3], d5[3], x4[3], y4[3], d4[3], x3[3], y3[3], d3[3], x2[3], y2[3], d2[3], x1[3], y1[3], d1[3]; //all coordinates for all ships
	int errors = 0;
	do {
		drawBoard(board,0);
		printf_s("\nCarrier's location! (size 5)\n");
		printf_s("Give me X: ");
		scanf_s(" %s", &x5, 3);
		printf_s("Give me Y: ");
		scanf_s(" %s", &y5, 3);
		printf_s("Give me d: ");
		scanf_s(" %s", &d5, 3);
		system("cls");
		errors = placeShip(5, validateInput(x5,1), validateInput(y5, 1), validateInput(d5, 2), board);
	} while (errors);
	do {
		drawBoard(board,0);
		printf_s("\nBattleship's location! (size 4)\n");
		printf_s("Give me X: ");
		scanf_s(" %s", &x4, 3);
		printf_s("Give me Y: ");
		scanf_s(" %s", &y4, 3);
		printf_s("Give me d: ");
		scanf_s(" %s", &d4, 3);
		system("cls");
		errors = placeShip(4, validateInput(x4, 1), validateInput(y4, 1), validateInput(d4, 2), board);
	} while (errors);
	do {
		drawBoard(board,0);
		printf_s("\nDestroyer's location! (size 3)\n");
		printf_s("Give me X: ");
		scanf_s(" %s", &x3, 3);
		printf_s("Give me Y: ");
		scanf_s(" %s", &y3, 3);
		printf_s("Give me d: ");
		scanf_s(" %s", &d3, 3);
		system("cls");
		errors = placeShip(3, validateInput(x3, 1), validateInput(y3, 1), validateInput(d3, 2), board);
	} while (errors);
	do {
		drawBoard(board, 0);
		printf_s("\nSubmarine's location! (size 3)\n");
		printf_s("Give me X: ");
		scanf_s(" %s", &x2, 3);
		printf_s("Give me Y: ");
		scanf_s(" %s", &y2, 3);
		printf_s("Give me d: ");
		scanf_s(" %s", &d2, 3);
		system("cls");
		errors = placeShip(3, validateInput(x2, 1), validateInput(y2, 1), validateInput(d2, 2), board);
	} while (errors);
	do {
		drawBoard(board, 0);
		printf_s("\nPatrol boat's location! (size 2)\n");
		printf_s("Give me X: ");
		scanf_s(" %s", &x1, 3);
		printf_s("Give me Y: ");
		scanf_s(" %s", &y1, 3);
		printf_s("Give me d: ");
		scanf_s(" %s", &d1, 3);
		system("cls");
		errors = placeShip(2, validateInput(x1, 1), validateInput(y1, 1), validateInput(d1, 2), board);
	} while (errors);
	system("cls");
}

void defaultShip(int board1[10][10], int board2[10][10]) {
	placeShip(5, 4, 1, 0, board1); // 4 1 0
	placeShip(4, 6, 6, 1, board1); // 6 6 1
	placeShip(3, 2, 9, 1, board1); // 2 9 1
	placeShip(3, 8, 9, 1, board1); // 8 9 1
	placeShip(2, 8, 2, 0, board1); // 8 2 0

	placeShip(5, 3, 3, 1, board2); // 4 1 0
	placeShip(4, 1, 5, 0, board2); // 6 6 1
	placeShip(3, 1, 2, 1, board2); // 2 9 1
	placeShip(3, 6, 6, 0, board2); // 8 9 1
	placeShip(2, 4, 7, 1, board2); // 8 2 0
}

int randomize(int x) {
	if (x == 1) {
		return (rand() % 2); //randomizes 0 or 1
	} else {
		return (1 + (rand() % x)); //randomizes int from 1 to a given number
	}
}

void randomizeShipLocation(int board1[10][10], int board2[10][10]) {
	int errors = 0;
	srand((unsigned int)time(NULL)); //is necessary for rand(). "(unsigned int)" to get rid of a warning C4244
	do { errors = placeShip(5, randomize(10), randomize(10), randomize(1), board1); } while (errors); //try untill you get it right, randomizer!!
	do { errors = placeShip(4, randomize(10), randomize(10), randomize(1), board1); } while (errors);
	do { errors = placeShip(3, randomize(10), randomize(10), randomize(1), board1); } while (errors);
	do { errors = placeShip(3, randomize(10), randomize(10), randomize(1), board1); } while (errors);
	do { errors = placeShip(2, randomize(10), randomize(10), randomize(1), board1); } while (errors);

	do { errors = placeShip(5, randomize(10), randomize(10), randomize(1), board2); } while (errors);
	do { errors = placeShip(4, randomize(10), randomize(10), randomize(1), board2); } while (errors);
	do { errors = placeShip(3, randomize(10), randomize(10), randomize(1), board2); } while (errors);
	do { errors = placeShip(3, randomize(10), randomize(10), randomize(1), board2); } while (errors);
	do { errors = placeShip(2, randomize(10), randomize(10), randomize(1), board2); } while (errors);
}