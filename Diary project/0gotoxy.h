#include <stdio.h>
#include <windows.h>


COORD coord={0,0}; // this is global variable 
                                    /*center of axis is set to the top left cornor of the screen*/ 
void gotoxy(int x,int y) 
{ 
    coord.X=x; 
    coord.Y=y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord); 
} 

// I have to make sure that if I am 
// making a diagonal line... then it must exist in the first place
void line(int x1, int y1, int x2, int y2)
{
    gotoxy(x1, y1);

    int x =x1,y=y1;
    while(1)
    {
        printf(".");
        if(x2-x > 0) x++; // lowering the gaps one at a time
        if(x2-x < 0) x--;

        if(y2 -y >0) y++;
        if(y2 - y <0) y--;

        gotoxy(x,y);

        if(x==x2   && y==y2) break; //arrived at out destination
    }

}

void glow_line(int x1, int y1, int x2, int y2)
{
    gotoxy(x1, y1);

    int x =x1,y=y1;
    while(1)
    {
        printf("\033[1;34m.\033[0m\n");
        if(x2-x > 0) x++; // lowering the gaps one at a time
        if(x2-x < 0) x--;

        if(y2 -y >0) y++;
        if(y2 - y <0) y--;

        gotoxy(x,y);

        if(x==x2   && y==y2) break; //arrived at out destination
    }

}

