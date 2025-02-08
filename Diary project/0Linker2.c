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

char filename[25];

#include <time.h>
#include <stdio.h> 
#include <string.h>
#include <conio.h>
#include "0gotoxy.h"
#include "0todolist2.h" 
#include "0Welcome.h"
#include "0NewEntry2.h" 
#include "0LoginPage2.h"
#include "0EditEntry3.h"// must be in the end only
#include "0Profile2.h"

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
    return last_idx +1; // hard code
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
    gotoxy(47,0);
    printf("\x1b[033m%s's Journal\x1b[0m", name);
    gotoxy(0, 0);
    printdate();
    gotoxy(0, 1);
    printtime();

        FILE *fptr1=NULL;
    fptr1=fopen(filename,"rb");

    if(fptr1 == NULL) 
    {
        printf("couldn't open file");
    }
    struct entry details;

    // gotoxy(0,3);
    // Printing all the entries

    int y =0;
    #define datex  62
    #define timex  77
    while(fread(&details,sizeof(details),1,fptr1))
    {
        if(details.index ==  current_glow)
        {
            
        printf("\033[1;33m");
        gotoxy(15,3 +y); // two tabs is 8
        printf("%d: ",details.index);
        printf("%s ",details.topic);

        gotoxy(datex,3 +y);
        printf("\t%s",details.date);

        gotoxy(timex ,3 +y);
        printf("\t%s ",details.time);
        printf("\033[0m");
        }
        else if(details.favourite ==1)
        {
        printf("\033[1;34m");
        gotoxy(15,3 +y);
        printf("%d: ",details.index);
        printf("%s ",details.topic);

        gotoxy(datex,3 +y);
        printf("\t%s",details.date);

        gotoxy(timex ,3 +y);
        printf("\t%s ",details.time);
        printf("\033[0m");

        }
        else
        {
        gotoxy(15,3 +y);
        printf("%d: ",details.index);
        printf("%s ",details.topic);

        gotoxy(datex,3 +y);
        printf("\t%s",details.date);

        gotoxy(timex ,3 +y);
        printf("\t%s",details.time);
        }
        printf("\n");
        y++;
    }
    //printing buttons
    //new entry
    gotoxy(120,1);
    if(current_glow == -1)
    {
        printf("\033[1;33mNew Entry\033[0m");
    }
    else
    {
        printf("New Entry");
    }

    //todo list
    gotoxy(120,10);
    if(current_glow == -2)
    {
        printf("\033[1;33mTo Do List\033[0m");
    }
    else
    {
        printf("To Do List");
    }

    //profile
    gotoxy(47,24);
    if(current_glow == -3)
    {
        printf("\033[1;32mMy Profile\033[0m");
    }
    else
    {
        printf("My Profile");
    }

    //Sign Out
    gotoxy(120,24);
    if(current_glow == -4)
    {
        printf("\033[1;31mSign Out\033[0m");
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

        if(current_glow== -3)
        {
            current_glow = 1;
        }
        else if(current_glow== -4)
        {
            current_glow = -2;
        }
        else if(current_glow== -2)
        {
            current_glow = -1;
        }
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
            current_glow = -4;
        }
        else if(current_glow== GetLastIdx(filename))
        {
            current_glow = -3;
        }
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

        else if(current_glow== -3)
        {
            current_glow = -4;
        }
        break;
    }

    case 'a':
    case 'A':
    case 75://for left arrow key
    {
        if(current_glow == -4)
        {
            current_glow = -3;
        }

         if(current_glow == -2)
        {
            current_glow =1;
        }
         if(current_glow == -1)
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
    MainWelcome();

    while(1)
    {   // everytime we want to print menu
        int choice = PrintMenu(filename);
        
    // so both PrintMenu and GetChoice work on the same page

        switch(choice)// this will be done via buttons
        {
            case -1:
                system("cls");
                int last_idx = GetLastIdx(filename);
                NewEntry(last_idx-1); // un-hard code
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
                ViewEntry(choice); // also edits

        }
    }
    
}