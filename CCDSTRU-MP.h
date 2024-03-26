#include <stdio.h>

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

    if(*next)
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
OverCheck( int * over, int Areas[][2], int Board[][6]) //checks if the game is over
{
    int i, j, ctr = 0;

    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){
            if(Board[i][j] == 0)
                ctr++
        }
    }

    if(ctr == 0)
        *over = 1;

    if(Areas[0][0] == Areas[1][1] && Areas[1][1] == 1)
        *over = 1;
    if(Areas[0][0] == Areas[1][1] && Areas[1][1] == 2)
        *over = 2;
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


    if (!*over && *next && Board[PosR-1][PosC-1] == 0 )
    {
        good = !good;
        Board[PosR - 1][PosC - 1] = 1;
    }

    OverCheck( *over, Areas, Board);
    
    if (!*over && !*next && Board[PosR-1][PosC-1] == 0 )
    {
        good = !good;
        Board[PosR - 1][PosC - 1] = 2;
    }

    OverCheck( *over, Areas, Board);

    if (!*over && !good && *next && (Cardinality(Board, *next) > CardinalityC(Areas, *next))){
        Areas[c - 1][d - 1] = 1;
    }

    OverCheck( *over, Areas, Board);
    
    if (!*over && !good && !*next && (Cardinality(Board, *next) > CardinalityC(Areas, *next))){
        Areas[c - 1][d - 1] = 2;
    }

    OverCheck( *over, Areas, Board);
    
    if (!*over && !good) 
    {
        good = !good; 
    }
}
