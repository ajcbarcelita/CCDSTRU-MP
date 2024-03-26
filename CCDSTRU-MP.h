#include <stdio.h>

int
Cardinality(int Board[][6])
{
    if(Board[0][0] == Board[0][2] && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[2][0] == Board[2][2] && Board[2][2] == 1)
    {
        return 1;
    }
    if(Board[0][0] == Board[0][2] && Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[2][0] == Board[2][2] && Board[2][2] == 2)
    {
        return 1;
    }
}


void
NextPlayerMove( int PosR, int PosC, int * over, int * next, int * good, 
                int Board[][6])
{
    int i, j, k;

    int c = ((PosR-1)/3) + 1;
    int d = ((PosC-1)/3) + 1;


    if (!*over && !*next && Board[PosR-1][PosC-1] == 0 )
    {
        *good = !*good;
        Board[PosR-1][PosC-1] = 1;
    }

    if (!*over && *next && Board[PosR-1][PosC-1] == 0 )
    {
        *good = !*good;
        Board[PosR-1][PosC-1] = 2;
    }

    if (!*over && *good && *next && )

    if (!*over && *good == 1) 
    {
        *good = !*good; 
    }
}