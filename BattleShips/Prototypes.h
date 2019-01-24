#pragma once

struct loaded {
	int roundNumber;
	int board1[10][10];
	int board2[10][10];
};

//Handling.h
void color(int c);
void drawBoard(int board[10][10], int hidden);
int checkWin(int board[10][10]);
void changePlayerInfo(int roundNumber, int board1[10][10], int board2[10][10]);
void gameWon(int roundNumber, int board1[10][10], int board2[10][10]);
int menu(int board1[10][10], int board2[10][10]);
void help();
int validateInput(char x[3], int option);
//Ships.h
int placeShip(int s, int x, int y, int d, int board[10][10]);
void scanShipLocation(int board[10][10]);
void defaultShip(int board1[10][10], int board2[10][10]);
int randomize(int x);
void randomizeShipLocation(int board1[10][10], int board2[10][10]);
//Fure.h
int shoot(int x, int y, int board[10][10]);
void scanFireLocation(int board[10][10]);
//Save.h
void saveGame(int roundNumber, int board1[10][10], int board2[10][10]);
loaded loadGame();