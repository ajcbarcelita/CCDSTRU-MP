 #include <stdio.h>
 #include "CCDSTRU-MP.h"
 
 int main()
 {
	int over = 0;
	int next = 0;
	int PosR, PosC;

	int Board[6][6] = {0}; // board is f 6x6 board
	int Areas[2][2] = {0}; // areas is c 2x2 board -- win con


 	NextPlayerMove(PosR, PosC, &over, &next, Board);
 	return 0;
 }
