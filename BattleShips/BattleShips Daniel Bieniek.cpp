#include "stdafx.h" //predefined in VS
#include <stdio.h> //predefined in VS
#include <conio.h> //predefined in VS
#include <tchar.h> //predefined in VS
#include <string.h>
#include <windows.h> //for coloring text in console
#include <time.h> //for rand()
//CUSTOM LIBRARIES
#include "Prototypes.h"
#include "Handling.h"
#include "Ships.h"
#include "Fire.h"
#include "Save.h"

int main()
{
	int board1[10][10] = {};	//creates first board 10x10
	int board2[10][10] = {};	//creates second board 10x10
	int ifWin = 0; //flag for winning
	int roundNumber = 0;
	int menuOutput;
	menuOutput = menu(board1, board2); //avaiable outputs: -1 - unsuspected, -2 - exit, -3 - load game error, >= 0 - a round number
	if (menuOutput == -2) { //Exit
		color(3);
		return 0;
		color(0);
	}
	else if (menuOutput == -3) { //no autoSave.txt file when "Load Game" was chosen
		system("cls");
		color(1);
		printf_s("Game could not be loaded. Start a New Game.\n");
		color(0);
		main();
	}
	else if (menuOutput >= 0) { //the game has started or is continuing from a loaded state
		roundNumber = menuOutput;
	}
	while (!ifWin) { //change player, keep playing untill the game is won
		changePlayerInfo(roundNumber, board1, board2);
		if (roundNumber % 2 == 0) { //for even round number the PLAYER ONE has a move
									//this is why, it was harder, to make one player, play again after successful hit
			color(4);
			printf_s("\n       PLAYER ONE\n");
			color(0);
			drawBoard(board1, 0);
			drawBoard(board2, 1);
			scanFireLocation(board2); //scans user input for fire location
			ifWin = checkWin(board2);
		}
		else { //for odd round number the PLAYER TWO has a move
			color(5);
			printf_s("\n       PLAYER TWO\n");
			color(0);
			drawBoard(board2, 0);
			drawBoard(board1, 1);
			scanFireLocation(board1);
			ifWin = checkWin(board1);
		}
		roundNumber++;
	}
	gameWon(roundNumber - 1, board1, board2);
	color(3);
	return 0;
}