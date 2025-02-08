#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "0datetime.h"
// #include "0gotoxy.h"
void delay(int milliseconds)
{
    Sleep(milliseconds);
}
//global Variable
char name[50];

void welcome(char name[])
{
    int random_number = rand() % 3;

    char Quotes[100][100] = {
        "Life is like riding a bicycle. To keep your balance, you must keep moving",
        "Life is really simple, but we insist on making it complicated",
        "harder choice require the strongest will.... \n",
    };
    gotoxy(35,5);
    for (int i = 0; i < 50; i++)
    {
        printf("\x1b[34m_\x1b[0m");
        delay(50);
    }
    system("cls");
    gotoxy(47,0);
    printf("\x1b[34mWelcome to the diary MENU\x1b[0m");
    gotoxy(53, 2);
    printf("Hello \x1b[33m%s\x1b[0m", name);
    gotoxy(0, 0);
    printdate();
    gotoxy(0, 1);
    printtime();
    printf("\n\n\nHope your day is going well. Welcome to the Dairy Menu.\n");    // Yellow
    printf("The Quote of the day is:\n\x1b[32m%s\x1b[0m", Quotes[random_number]); // Green
}

void setupmenu()
{
    // while (1)
    // {
        gotoxy(0, 0);
        printdate();
        gotoxy(0, 1);
        printtime();
        gotoxy(51,0);
        printf("WELCOME");
        gotoxy(45, 3);
        printf(" \x1b[33mEnter your Name: \x1b[0m");
        scanf("%s", name);
        system("cls");
        welcome(name);
        getchar();
        getchar();
        system("cls");
    // }
}

void MainWelcome()
{
    srand(time(NULL));
    system("cls");
    setupmenu();
    return ;
}

