 #include <stdio.h>
 #include <stdlib.h>
 #include "CCDSTRU-MP.h"
 
 /*
 	Take note of the following things.
 	
 	For the over, next, and good variables, 0 means FALSE, 1 means TRUE.
 	Player A is represented by the number 1 in the board and areas array.
 	Player B is represented by the number 2 instead.
 */

 int main()
 {
	int over = 0; //indicator of the current state of the game, 0 means game is not over, 1 means game is over
	int next = 0; //next indicates who the current player is, 0 means it is Player A's turn, 1 means it is Player B's turn
	int PosR, PosC; //coordinates that a player inputted, PosR = row, PosC = col
	
	//if a player inputs a coordinate that is currently empty, good becomes 1, prompts program to check if the player completed 
	//one of the 4 patterns in the 6x6 board
	int good = 0; 
	
	//turn only counts the number of turns so far, which is used to compute turnStatus
	//turnStatus = turn % 2, if 0, it's A's turn, if 1, it's B's turn
	int turn = 0;
	int turnStatus;
	 
	char Board[6][6] = {'0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0'}; // board is F, 6x6 board
	char Areas[2][2] = {'0','0','0','0'}; // areas is C, 2x2 board -- win con
	
	//while loop continues as long as the game is not over
	while (!over) {
		system("cls");
		printf("=== MODIFIED TIC-TAC-TOE ===\n\n");
		printBoard(Board);
		turnStatus = turn % 2;
		if (turnStatus == 0)
			printf("It is currently Player A's turn.\n\n");
		else 
			printf("It is currently Player B's turn.\n\n");
		
		inputPos(&PosR, &PosC);
		NextPlayerMove(PosR, PosC, &over, &next, &good, Board, Areas);
		GameOver(&over, &next, Board, Areas);
		turn++;
	}
			
 	return 0;
 }
 
 
 
 
