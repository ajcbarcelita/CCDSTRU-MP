#include <stdio.h>

typedef char String[7];

//input function for the game, takes in a value between 1 to 6 for PosR and PosC
void inputPos(int *PosR, int *PosC)
{
	//func repeats if you enter any value less than 1 or more than 6
	//loop only stops if you enter a valid number, which ensures that coordinate input is always valid
    do
    {
        printf("Enter a number for row [1 - 6]: ");
        scanf("%d", PosR);
        printf("Enter a number for col [1 - 6]: ");
        scanf("%d", PosC);

        if ( (*PosR < 1 || *PosR > 6) || (*PosC < 1 || *PosC > 6) ) {
            printf("INVALID INPUT! Please only enter a number from 1 to 6.\n\n");
        }
        
    } while ( (*PosR < 1 || *PosR > 6) || (*PosC < 1 || *PosC > 6) );  
}

//this function simply prints out the board using a for loop
void printBoard(int Board[][6])
{
    int i, j;

    for (i = 0; i < 6; i++) {
        printf("=========================\n");
        for (j = 0; j < 6; j++) {
            printf("| %d ", Board[i][j]);
        }
        printf("|\n");
    }
    printf("=========================\n\n");
}

//Cardinality function counts the cardinality of the powerset of F1 and f2 that intersects with Set S
int
Cardinality(int Board[][6], int * next)
{

    int cardinality1 = 0, cardinality2 = 0;
    
    if(Board[0][0] == Board[0][2] && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[2][0] == Board[2][2] && Board[2][2] == 1) //compares with the first element of set S
    {
        cardinality1++; 
    }
    if(Board[0][0] == Board[0][2] && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[2][0] == Board[2][2] && Board[2][2] == 2) //the first element of set S
    {
        cardinality2++;
    }

    if(Board[3][3] == Board[3][5] && Board[3][5] == Board[4][4] && Board[4][4] == Board[5][3] && Board[5][3] == Board[5][5] && Board[5][5] == 1) 
    {
        cardinality1++; 
    }
    if(Board[3][3] == Board[3][5] && Board[3][5] == Board[4][4] && Board[4][4] == Board[5][3] && Board[5][3] == Board[5][5] && Board[5][5] == 2) 
    {
        cardinality2++;
    }

    if(Board[0][4] == Board[1][3] && Board[1][3] == Board[1][4] && Board[1][4] == Board[1][5] && Board[1][5] == Board[2][4] && Board[2][4] == 1) 
    {
        cardinality1++; 
    }
    if(Board[0][4] == Board[1][3] && Board[1][3] == Board[1][4] && Board[1][4] == Board[1][5] && Board[1][5] == Board[2][4] && Board[2][4] == 2) 
    {
        cardinality2++; 
    }

    if(Board[3][0] == Board[3][2] && Board[3][2] == Board[4][0] && Board[4][0] == Board[4][2] && Board[4][2] == Board[5][0] && Board[5][0] == Board[5][2] && Board[5][2] == 1)     
    {
        cardinality1++; 
    }
    if(Board[3][0] == Board[3][2] && Board[3][2] == Board[4][0] && Board[4][0] == Board[4][2] && Board[4][2] == Board[5][0] && Board[5][0] == Board[5][2] && Board[5][2] == 2)     
    {
        cardinality2++; 
    }

    if(!*next)
        return cardinality1;
    else
        return cardinality2;
}

//CardinalityC function counts the cardinality of both Set C1 and C2
int
CardinalityC(int Areas[][2], int * next)
{
    int i, j, cardinality1 = 0, cardinality2 = 0;

    for(i = 0; i < 2; i++){
        for(j = 0; j < 2; j++){
            if(Areas[i][j] == 1)
                cardinality1++;
            if(Areas[i][j] == 2)
                cardinality2++;
        }
    }

    if(!*next)
        return cardinality1;
    else
        return cardinality2;
}

//ismply checks if the game is over, based on the over biconditional in the system facts
void
OverCheck(int * over, int Areas[][2], int Board[][6]) //checks if the game is over
{
    int i, j, ctr = 0;
	
	//this loop counts the number of empty tiles (F3), aka number of tiles that are currently set to 0 in Board
    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){
            if(Board[i][j] == 0)
                ctr++;
        }
    }
	
	//if |F3| == 0, then game is over
    if(ctr == 0)
        *over = 1;
	
	//other conditions for game to be over
    if(Areas[0][0] == Areas[1][1] && Areas[1][1] == 1)
        *over = 1;
    if(Areas[0][0] == Areas[1][1] && Areas[1][1] == 2)
        *over = 1;
    if(Areas[0][1] == Areas[1][0] && Areas[1][0] == 1)
        *over = 1;
    if(Areas[0][1] == Areas[1][0] && Areas[1][0] == 2)
        *over = 1;
}

//this is programmed according to machine project specs
void
NextPlayerMove( int PosR, int PosC, int * over, int * next, int * good, int Board[][6], int Areas[][2])
{
	
	//these floor functions results in either 1 or 2, to be used in the Areas array
    int c = ( (PosR-1) / 3) + 1; 
    int d = ( (PosC-1) / 3) + 1;

	//checks if Player A's move is on an empty tile, if yes, puts 1 on the board, and good changes to true
	//when good becomes true, prompts program to check if the player has completed a winning pattern in any of the sectors as described by Set S
    if (!*over && !*next && Board[PosR-1][PosC-1] == 0 )
    {
        *good = !*good;
        Board[PosR - 1][PosC - 1] = 1;
    }

    OverCheck(over, Areas, Board); //checks if game is over
    
    //checks if Player B's move is on an empty tile, if yes, puts 2 on the board, and good changes to true
	//when good becomes true, prompts program to check if the player has completed a winning pattern in any of the sectors as described by Set S
    if (!*over && *next && Board[PosR-1][PosC-1] == 0 )
    {
        *good = !*good;
        Board[PosR - 1][PosC - 1] = 2;
    }

    OverCheck(over, Areas, Board); //checks if game is over
	
	//if player A has completed any winning pattern among the sectors as described in Set S
	//then put 1 in the coordinates (c - 1, d - 1) in the Areas array 
    if (!*over && *good && !*next && (Cardinality(Board, next) > CardinalityC(Areas, next))){
        Areas[c - 1][d - 1] = 1;
    }

    OverCheck(over, Areas, Board); //checks if game is over
    
    //if player B has completed any winning pattern among the sectors as described in Set S
	//then put 2 in the coordinates (c - 1, d - 1) in the Areas array 
    if (!*over && *good && *next && (Cardinality(Board, next) > CardinalityC(Areas, next))){
        Areas[c - 1][d - 1] = 2;
    }

    OverCheck(over, Areas, Board); //checks if game is over
    
    //if the game is not over, this resets the value of good back to 0 / FALSE
    if (!*over && *good) 
    {
        *good = !*good; 
    }
}


//simply counts the number of empty tiles (aka |F3|, or the tiles currently set to 0 in the Board)
int
checkF3(int Board[][6])
{
	int i, j, ctr = 0;

    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){
            if(Board[i][j] == 0)
                ctr++;
        }
    }
    
    return ctr;
}

//this function is called everytime after NextPlayerMove function is called
//this follows the machine project specifications
void
GameOver(int * over, int * next, int Board[][6], int Areas[][2])
{
    String result[2] = {"B wins", "A wins"};
	
	//basically if player A wins 
    if(*over && !*next && ((Areas[0][0] == Areas[1][1] && Areas[1][1] == 1) || (Areas[0][1] == Areas[1][0] && Areas[1][0] == 1))) {
    	system("cls");
    	printBoard(Board);
    	printf("%s\n", result[1]);
	} 
	
	//basically if player B wins
	else if(*over && *next && ((Areas[0][0] == Areas[1][1] && Areas[1][1] == 2) || (Areas[0][1] == Areas[1][0] && Areas[1][0] == 2))) {
		system("cls");
    	printBoard(Board);
    	printf("%s\n", result[0]);
	}
	
	//basically if board ran out of empty tiles AND both players did not fulfill the diagonal requirement to win as seen in Set P
    else if (checkF3(Board) == 0) {
    	system("cls");
    	printBoard(Board);
    	printf("No one wins. It's a draw.");
	}
    
    else //if game is not over, just switch turns
        *next = !*next;
}
