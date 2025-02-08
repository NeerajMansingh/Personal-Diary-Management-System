// All structures here
typedef struct entry
{
    int index;
    char content[2000];
    char * date;
    char * time;
    char topic[50];
    char favourite; // 0 or 1
    int current_line;
}entry;

#include <time.h>
#include <stdio.h> 
#include <string.h>
#include <conio.h>
#include "0gotoxy.h"
#include "0LoginPage.h"
#include "0todolist.h" 
#include "0NewEntry2.h"
#include "0EditEntry.h"
#include "0Welcome.h"
#include "0profile.h"

int GetLastIdx(char filename[])
{
    FILE * f = fopen(filename,"rb");
    entry E;

    int last_idx = 0;
    while(1)
    {
        
        if(fread(&E,sizeof(E),1,f)==0)
        {
            break;
        }
        last_idx = E.index;

    }
    return last_idx;
}


int current_glow = -1; // initial to -1
// 1-> first entry
// 2 -> seconde entry
// and so on
// -1 -> add entry
// -2 -> todolist
// -3 -> profile
// -4 -> close

int PrintMenu(char filename[])
{
    int last_idx = GetLastIdx(filename);
    char choice; // up down left right enter

    while(1)
    {
        system("cls");
        // gotoxy(20,10);
        // //printf("%d", current_glow);  dont need this NOW...I know it works now
        // gotoxy(0,0);

        FILE *fptr1=NULL;
    fptr1=fopen(filename,"rb");

    if(fptr1 == NULL) 
    {
        printf("couldn't open file");
    }
    struct entry details;

    // Printing all the entries
    while(fread(&details,sizeof(details),1,fptr1))
    {
        if(details.index ==  current_glow)
        {
            printf("\033[1;33m");
        printf("Entry number %d: ",details.index);
        printf("%s\n ",details.topic);
        printf("%s\n ",details.date);
        printf("%s\n ",details.time);
        printf("\033[0m\n");
        }
        else if(details.favourite ==1)
        {
            printf("\033[1;34m");
        printf("Entry number %d: ",details.index);
        printf("%s\n ",details.topic);
        printf("%s\n ",details.date);
        printf("%s\n ",details.time);
        printf("\033[0m\n");

        }
        else
        {
        printf("Entry number %d: ",details.index);
        printf("%s\n ",details.topic);
        printf("%s\n ",details.date);
        printf("%s\n ",details.time);
        }
        printf("\n\n");
    }
    //printing buttons
    //new entry
    gotoxy(60,0);
    if(current_glow == -1)
    {
        printf("\033[1;33mNew Entry\033[0m\n");
    }
    else
    {
        printf("New Entry");
    }

    //todo list
    gotoxy(60,5);
    if(current_glow == -2)
    {
        printf("\033[1;33mTo Do List\033[0m\n");
    }
    else
    {
        printf("To Do List");
    }

    //profile
    gotoxy(60,10);
    if(current_glow == -3)
    {
        printf("\033[1;33mMy Profile\033[0m\n");
    }
    else
    {
        printf("My Profile");
    }

    //Sign Out
    gotoxy(100,0);
    if(current_glow == -4)
    {
        printf("\033[1;31mSign Out\033[0m\n");
    }
    else
    {
        printf("Sign Out");
    }


    // logic for changing current_glow
    gotoxy(100,12);
    fflush(stdin);
    choice = getche();
    switch(choice)
    {
    case 'w':
    case 'W':
    case 72:// for up arrow key
    {
        if(current_glow >1) // also excludes the special buttons
        current_glow--;

        if(current_glow== -2)
        {
            current_glow = -1;
        }
        else if(current_glow== -3)
        {
            current_glow = -2;
        }
        // if(current_glow== -1)
        // {
        //     current_glow = -3;
        // }
        break;
    }

    case 's':
    case 'S':
    case 80://for down arrow key

    {
        if(0< current_glow && current_glow < last_idx)
        current_glow++;

        if(current_glow == -1)
        {
            current_glow = -2;
        }

        else if(current_glow== -2)
        {
            current_glow = -3;
        }
        // if(current_glow== -3)
        // {
        //     current_glow = -1;
        // }
        break;
    }

     case 'd':
    case 'D':
    case 77://for right arrow key
    {
        if(current_glow>0)
        {
            current_glow = -1;
        }   

        else if(current_glow <0)
        {
            current_glow = -4;
        }
        break;
    }

    case 'a':
    case 'A':
    case 75://for left arrow key
    {
        if(current_glow = -4)
        {
            current_glow = -1;
        }

        if(current_glow <0)
        {
            current_glow =1;
        }

        
        break;
    }

    case '\r': // carriage return
    {
        return current_glow;
    }

    }

}
}


int main()
{
    LoginPage();
    //MainWelcome();
    while(1)
    {   // everytime we want to print menu
        int choice = PrintMenu(filename);
        
    // so both PrintMenu and GetChoice work on the same page

        switch(choice)// this will be done via buttons
        {
            case -1:
                system("cls");
                int last_idx = GetLastIdx(filename);
                NewEntry(last_idx);
                break;

            case -2:
                system("cls");
                ToDoList();
                break;

            case -3:
                system("cls");
                ProfilePage();
                break;

            case -4:
                system("cls");
                printf("bye");
                exit(0);
                break;

            default: // view entry scenario
                system("cls");
                ViewEntry(filename,choice);

        }
    }
    
}