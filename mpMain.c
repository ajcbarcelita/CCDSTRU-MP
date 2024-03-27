 #include <stdio.h>
 #include <stdlib.h>
 #include "CCDSTRU-MP.h"
 
 int main()
 {
	int over = 0;
	int next = 0;
	int good = 0;
	int PosR, PosC;
	int turn = 0;
	 
	int Board[6][6] = {0}; // board is f 6x6 board
	int Areas[2][2] = {0}; // areas is c 2x2 board -- win con

	while (!over) {
		system("cls");
		printBoard(Board, Areas);
		printf("It is currently Player %d's turn.\n\n", turn % 2 + 1);
		inputPos(&PosR, &PosC);
		NextPlayerMove(PosR, PosC, &over, &next, &good, Board, Areas);
		GameOver(&over, &next, Board, Areas);
		turn++;
	}		
	 
 	return 0;
 }
 
 
 
 
