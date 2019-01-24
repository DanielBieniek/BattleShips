#pragma once

void color(int c) {
	HANDLE hOut; //creating a variable of type HANDLE
	hOut = GetStdHandle(STD_OUTPUT_HANDLE); //attaching a handle to the variable for later use
	switch (c) {
		case 0: //white
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			break;
		case 1: //red
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			break;
		case 2: //green
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
			break;
		case 3: //grey
			SetConsoleTextAttribute(hOut, FOREGROUND_RED & FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			break;
		case 4: //turquoise (PLAYER ONE)
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE);
			break;
		case 5: //violet (PLAYER TWO)
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE);
			break;
		case 6: //yellow
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			break;
		default: //invalid, change to white
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
			break;
	}
}

void drawBoard(int board[10][10], int hidden) {
	unsigned char square = 254, shipPart = 'O', hit = 'X', undefined = '?'; //characters displayed in console instead of raw data
	for (int i = -1; i < 10; i++) { //starts from -1 to print coordinates
		for (int j = -1; j < 10; j++) {
			if (i == -1 && j == -1) {
				printf_s("  ");
			} else if (i == -1) { // draw horizontal 1-10
				printf_s("%2d", j + 1);
			} else if (j == -1) { // draw vertical 1-10
				printf_s("%2d", i + 1);
			} else {
				switch (board[i][j]) { //change value in table to 'graphics'
				case 0: //water
					printf_s("%2c", square); //white square
					break;
				case 1: //ship part
					if (!hidden) {
						color(2);
						printf_s("%2c", shipPart); //green O
						color(0);
					} else { //don't show opponents ship parts, draw them like water
						printf_s("%2c", square);
					}
					break;
				case 2: //hit part
					color(1);
					printf_s("%2c", hit); //red X, for hit part
					color(0);
					break;
				case 3: //hit water
					color(3);
					printf_s("%2c", hit); //gray X, for hit water
					color(0);
					break;
				default:
					printf_s("%2c", undefined); //if somehow a data is what it shouldn't supposed be, print the question mark
					break;
				}

			}
		}
		printf_s("\n");
	}
	printf_s("\n");
}

int checkWin(int board[10][10]) {
	int parts = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == 1) {
				parts++; //sums up all the un-hit parts still on the board
			}
		}
	}
	if (parts) {
		return 0; //if any part exists, nothing happens
	} else {
		return 1; //if no parts are present, than a player won
	}
}

void changePlayerInfo(int roundNumber, int board1[10][10], int board2[10][10]) {
	system("cls");
	saveGame(roundNumber, board1, board2); //saves game right before another player starts their round
	char enter = 0; //used for "Press any key to continue" trick
	if (roundNumber == -2) { //negative round if the ships aren't set yet, PLAYER ONE places their ships
		color(4);
		printf_s("\nPLAYER ONE");
		color(0);
		printf_s(" chooses the location of their ships!\n");
		color(3);
		printf("Press any key to continue\n");
		color(0);
		enter = _getch();
	} else if(roundNumber == -1) { //negative round if the ships aren't set yet, PLAYER TWO places their ships
		color(5);
		printf_s("\nPLAYER TWO");
		color(0);
		printf_s(" chooses the location of their ships!\n");
		color(3);
		printf("Press any key to continue\n");
		color(0);
		enter = _getch();
	} else if (roundNumber % 2 == 0) { //even numbers, PLAYER ONE makes a move
		printf_s("\nIt's ");
		color(4);
		printf_s("PLAYER ONE");
		color(0);
		printf_s("'s %d. round!\n", (roundNumber / 2) + 1); //calculates individual round number. half of total.
		printf_s("PLAYER TWO should turn around.\n");
		color(3);
		printf("Press any key to continue\n");
		color(0);
		enter = _getch();
	} else {  //odd numbers, PLAYER TWO makes a move
		printf_s("\nIt's ");
		color(5);
		printf_s("PLAYER TWO");
		color(0);
		printf_s("'s %d. round!\n", ((roundNumber - 1) / 2) + 1); //calculates individual round number. half of total.
		printf_s("PLAYER ONE should turn around.\n");
		color(3);
		printf("Press any key to continue\n");
		color(0);
		enter = _getch();
	}
	fflush(stdin); //to clear "Press any key to continue" trick
	system("cls");
}

void gameWon(int roundNumber, int board1[10][10], int board2[10][10]) {
	system("cls");
	if (roundNumber % 2 == 0) { //if the game was won when the roundNumber counter was even, PLAYER ONE won
		color(4);
		printf_s("\nPLAYER ONE");
		color(0);
		printf_s(" WON THE GAME IN %d ROUNDS\n\n", (roundNumber / 2) + 1);
	} else { //if the game was won when the roundNumber counter was odd, PLAYER TWO won
		color(5);
		printf_s("\nPLAYER TWO");
		color(0);
		printf_s(" WON THE GAME IN %d ROUNDS\n\n", ((roundNumber - 1) / 2) + 1);
	}
	char enter = 0;
	enter = _getch(); //"Press any key to continue" trick again
	fflush(stdin);
	menu(board1, board2);
}

int menu(int board1[10][10], int board2[10][10]) {
	color(6);
	printf_s("\n          MENU\n\n");
	color(0);
	printf_s("1. Set ship location.\n");
	printf_s("2. Use default ship location.\n");
	printf_s("3. Randomize ship location.\n");
	printf_s("4. Load game.\n");
	printf_s("5. Help\n");
	printf_s("0. Exit game.\n");

	int roundNumber;
	char choice[3];
	printf_s("\n\tYour choice: ");
	scanf_s(" %s", choice, 3);

	switch (validateInput(choice,0)) {
		case 1: // Set ship location
			changePlayerInfo(-2, board1, board2);
			scanShipLocation(board1); //scans user1 input for ship location
			changePlayerInfo(-1, board1, board2);
			scanShipLocation(board2); //scans user2 input for ship location
			break;
		case 2: // Use default ship location
			defaultShip(board1, board2);
			break;
		case 3: // Randomize ship location
			randomizeShipLocation(board1, board2);
			break;
		case 4: // Load game
			struct loaded load = loadGame(); //call loadGame()
			roundNumber = load.roundNumber;
			if (roundNumber != -3) { //if -3, than "no saveFile.save" error is returned and delt with in main()
				memcpy(board1, load.board1, sizeof(load.board1)); //writes the boards read from the file into 2d arrays
				memcpy(board2, load.board2, sizeof(load.board2));
			}
			return roundNumber;
			break;
		case 5: // Help
			help();
			menu(board1, board2);
			break;
		case 0: // Exit game
			return -2; //output is processed in main()
		default: // Invalid input
			system("cls");
			color(1);
			printf_s("Invalid input.\n");
			color(0);
			menu(board1, board2);
			break;
	}
	return -1;
}

void help() { //help message
	system("cls");
	printf_s("\n======================================================\n");
	printf_s("          HELP\n\n");
	color(6);
	printf_s("\tRULES:\n");
	color(0);
	printf_s("https://www.hasbro.com/common/instruct/BattleShip_(2002).PDF \n\n");
	printf_s("Use X for vertical coordinate,\n");
	printf_s("And Y for horizontal coordinate.\n");
	printf_s("'d' stands for 'direction',\n");
	printf_s("0 - horizontal\n");
	printf_s("1 - vertical\n");
	color(6);
	printf_s("\n\tMenu options explained:\n");
	color(0);
	printf_s("1 - Asks the player to set their ships location.\n");
	printf_s("2 - Uses default ship location.\n");
	printf_s("3 - Randomizes ship location for both players.\n");
	printf_s("4 - Loads the game with most recent state\n from autoSave.txt file.\n");
	printf_s("5 - Displays this help message.\n");
	printf_s("0 - Exits the game.\n");
	color(6);
	printf_s("\n\tAuto saving:\n");
	color(0);
	printf_s("Game saves automatically with every\n successfully played round.\n");
	printf_s("You can load the save by choosing\n \"Load Game\" from the menu.\n");
	printf_s("If you want to have more than one game saved\n I suggest you to change the file name.\n");
	printf_s("But remember to change the save name back to\n autoSave before loading it to the game.\n");
	printf_s("======================================================\n\n");
}

int validateInput(char x[3], int option) { //used for all user-scanned variables, to prevent the game from going wild. It was a challenge to come up with the solution.
	//option: 0 = menu, 1 = 1-10, 2 = 0-1
	if (option == 0) { //menu
		if (!strcmp(x, "1") ||
			!strcmp(x, "2") ||
			!strcmp(x, "3") ||
			!strcmp(x, "4") ||
			!strcmp(x, "5") ||
			!strcmp(x, "0")) {
				return atoi(x); //change this string into int, and use it in menu()
		} else {
			return -1; //output incorrect menu option (but of type int) when invalid input was given
		}
	} else if (option == 1) { //coordinates, 1-10
		if (!strcmp(x, "1") ||
			!strcmp(x, "2") ||
			!strcmp(x, "3") ||
			!strcmp(x, "4") ||
			!strcmp(x, "5") ||
			!strcmp(x, "6") ||
			!strcmp(x, "7") ||
			!strcmp(x, "8") ||
			!strcmp(x, "9") ||
			!strcmp(x, "10")) {
				return atoi(x); //change this string into int, and use given coordinate in scanShipLocation() and scanFireLocation()
		}
		else {
			return 0; //output out-of-bands coordinate (but of type int) when invalid input was given
		}
	} else if (option == 2) { //direction 0/1
		 if (!strcmp(x, "0") ||
			 !strcmp(x, "1")) {
				 return atoi(x); //change this string into int, and use given direction in scanShipLocation()
		 }
		 else {
			 return 2; //output incorrect direction (but of type int) when invalid input was given
		 }
	} else { // safety measure, wrong 'option' variable should never be given
		return atoi(x);
	}
	return 0;
}