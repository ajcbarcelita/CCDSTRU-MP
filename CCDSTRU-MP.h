#include <stdio.h>

typedef char String[7];

//input function for the game
void inputPos(int *PosR, int *PosC)
{
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

void printBoard(int Board[][6], int Areas[][2])
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
    
    for (i = 0; i < 2; i++) {
        printf("=========\n");
        for (j = 0; j < 2; j++) {
            printf("| %d ", Areas[i][j]);
        }
        printf("|\n");
    }
    printf("=========\n");
    
}


int
Cardinality(int Board[][6], int * next) //count the cardinality of the power set of F1 or F2 intersected with set S
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

    if(*next)
        return cardinality1;
    else
        return cardinality2;
}

void
OverCheck(int * over, int Areas[][2], int Board[][6]) //checks if the game is over
{
    int i, j, ctr = 0;

    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){
            if(Board[i][j] == 0)
                ctr++;
        }
    }

    if(ctr == 0)
        *over = 1;

    if(Areas[0][0] == Areas[1][1] && Areas[1][1] == 1)
        *over = 1;
    if(Areas[0][0] == Areas[1][1] && Areas[1][1] == 2)
        *over = 1;
    if(Areas[0][1] == Areas[1][0] && Areas[1][0] == 1)
        *over = 1;
    if(Areas[0][1] == Areas[1][0] && Areas[1][0] == 2)
        *over = 1;
}

void
NextPlayerMove( int PosR, int PosC, int * over, int * next, int Board[][6], int Areas[][2])
{
    int good = 0;

    int c = ( (PosR-1) / 3) + 1;
    int d = ( (PosC-1) / 3) + 1;


    if (!*over && !*next && Board[PosR-1][PosC-1] == 0 )
    {
        good = !good;
        Board[PosR - 1][PosC - 1] = 1;
    }

    OverCheck(over, Areas, Board);
    
    if (!*over && *next && Board[PosR-1][PosC-1] == 0 )
    {
        good = !good;
        Board[PosR - 1][PosC - 1] = 2;
    }

    OverCheck(over, Areas, Board);

    if (!*over && !good && !*next && (Cardinality(Board, next) > CardinalityC(Areas, next))){
        Areas[c - 1][d - 1] = 1;
    }

    OverCheck(over, Areas, Board);
    
    if (!*over && !good && *next && (Cardinality(Board, next) > CardinalityC(Areas, next))){
        Areas[c - 1][d - 1] = 2;
    }

    OverCheck(over, Areas, Board);
    
    if (!over && !good) 
    {
        good = !good; 
    }
}

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

void
GameOver(int * over, int * next, int Board[][6], int Areas[][2])
{
    String result[2] = {"B wins", "A wins"};

    if(*over && !*next && ((Areas[0][0] == Areas[1][1] && Areas[1][1] == 1) || (Areas[0][1] == Areas[1][0] && Areas[1][0] == 1)))
        printf("%s\n", result[1]);
    else if(*over && *next && ((Areas[0][0] == Areas[1][1] && Areas[1][1] == 2) || (Areas[0][1] == Areas[1][0] && Areas[1][0] == 2)))
        printf("%s\n", result[0]);
    else if (checkF3(Board) == 0) 
    	printf("No one wins. It's a draw.");
    else
        *next = !*next;
}
