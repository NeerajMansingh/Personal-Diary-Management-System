#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct user
// {
//     char name[50];
//     int Entries_So_Far;
//     // add more stuff later
// }user;

void NewEntry(int last_index)
{   
    FILE * fp;
    fp = fopen(filename, "rb+");
    fseek(fp,0,SEEK_END);
    char another = 'y';
   
   //starts
        entry E;
        E.index = last_index + 1;
        system("cls");
        printf("This is Entry Number %d\n",E.index);
        fflush(stdin);
        printf("Enter date: \n");
        gets(E.date);
        fflush(stdin);
        printf("Enter time: \n");
        gets(E.time);
        fflush(stdin);
        printf("\nToday's Topic Shall be: ");
        gets(E.topic);
        fflush(stdin);
        printf("Type Away: (click * and enter to end entry)\n");
        scanf("%[^*]s",E.content);
        fflush(stdin);
             

        fwrite(&E,sizeof(E),1,fp);
        //fputc('\n',fp ); // not sure if this will work
        printf("Entry Added Successfully.\n\n");
        
        printf("Another entry?(y/n)");
        // ideally I want to go back to the MENU after this is done in case of 'n
        scanf("%c",&another);
        fflush(stdin);
        if(another == 'y')
        {
            fclose(fp);
            NewEntry(last_index +1);
        }

        else
        {
            fclose(fp);
            return;
        }
}