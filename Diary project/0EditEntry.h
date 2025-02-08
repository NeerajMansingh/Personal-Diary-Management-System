
// typedef struct entry
// {
//     int index;
//     char content[2000];
//     char date[20];
//     char time[20];
//     char topic[50];
// }entry;

// typedef struct user
// {
//     char name[50];
//     int Entries_So_Far;
//     // add more stuff later
// }user;


 #include <stdio.h>
#include <stdlib.h>
#include <string.h>

void EditEntry(char filename[],int idx)
{
    FILE * fp = fopen(filename,"rb+");
    char newContent[2000];
    entry E;

    while(fread(&E,sizeof(E),1,fp)!= 0)
    {
        if(E.index == idx)
        {
            printf("Entry Found\n");
            printf("Current Entry:\n%s",E.content);
            printf("\nEnter New Entry:\n");
            scanf("%[^*]s",newContent);
            strcpy(E.content, newContent);
            fseek(fp, -sizeof(E),SEEK_CUR);
            fwrite(&E,sizeof(E),1, fp);
            printf("\n Okay.. entry updated successfully");
            printf("\nEnter to return to main menu");
            getchar();
            getchar();
            fclose(fp);
            return ;
        }
    } 

    printf("Entry Not Found, try again");
}

void ViewEntry( int idx)
{
    FILE * fp;
    fp = fopen(filename, "rb");
    char edit ;
    rewind(fp);
    // now I want to read entry number 1 from Samplefile.exe

    entry E;
    while(fread(&E,sizeof(E),1,fp)!= 0)
    {
        if(E.index == idx)
        {
            printf("Entry Found.\n\n");
            printf("Entry Number %d: %s\n", E.index, E.topic);
            printf("Date of Entry: %s\n",E.date);
            printf("Time of Entry: %s\n\n",E.time);
            printf("%s",E.content);
            getchar();
            printf("Do You Want to Edit this?y/n");
            scanf("%c", &edit);
            fflush(stdin);
            if(edit== 'y')
            {
                system("cls");
                EditEntry(filename, E.index);
            }
            fclose(fp);
            return ;
        }
    }
    // else for the while
    printf("Entry Not found");
}