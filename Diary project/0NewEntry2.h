#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char* getCurrentDate() {
    // Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

    // Format the date as a string
    static char dateBuffer[11]; // Buffer to store the date string (including null terminator)
    strftime(dateBuffer, sizeof(dateBuffer), "%d-%m-%Y", info);
    
    return dateBuffer;
}

char* getCurrentTime() {
    // Get current time
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

    // Format the time as a string
    static char timeBuffer[9]; // Buffer to store the time string (including null terminator)
    strftime(timeBuffer, sizeof(timeBuffer), "%H:%M:%S", info);
    
    return timeBuffer;
}


#define bx1 0
#define bx2 100
#define by1 4
#define by2 20
#define star_x 60
#define star_y by2 +2
int current_line =0; // global variable

#include "0EditContent.h" //vvimp

void AddSpace(char str[])
{
    int len = strlen(str);
    int len2 = len +2;
    char new_str[len2];
    new_str[0] =' ';
    new_str[1] =' ';
    int i = 0, j=2;

    while(i<len)
    {
        new_str[j] = str[i];
        i++;
        j++;
    }

    strcpy(str,new_str);
}

int MaxLines(char str[])
{
    int i =0, l=1;
    while(str[i] != '\0')
    {
        i++;
        if(str[i]== '\n')
        {
            l++;
        }
    }

    return l;
}

void PrintContent(int current, entry E)
{
    int line =1;
    int i =0;
   // int maxlines = MaxLines(content);
    while(i < strlen(E.content))
    {
        if(E.content[i] == '\n')
        {
            line++;
        }

        if(line == current)
        {
            printf("\033[1;34m%c\033[0m",E.content[i]);
            i++;
        }
        else
        {
            printf("%c",E.content[i]);
            i++;
        }
    }

}

void drawEditor(char current,entry E)
{
    system("cls");

        // strings toh print karo
        gotoxy(bx1+1,by1+1);
        // printf("%s",E.content);
        PrintContent(current_line,E);
        
        gotoxy(48,0);
        printf("%s",E.topic);


        //entry num
        gotoxy(0,by2+2);
        printf("This is Entry Number %d",E.index);
        
        //topic
        gotoxy(40,0);
        if(current == 't') printf("\033[1;34mTopic: \033[0m");
        else printf("Topic: ");

        //exit part
        gotoxy(bx2 + 8,0);
        if(current == 'e') printf("\033[1;31mSave And Exit\033[0m");
        else printf("Save And Exit");

        // this bit
        gotoxy(0,3);
        printf("Type Away: (click * and enter to end entry)\n");

        //time n date
        gotoxy(0,2);
        printf("\t\t\t\t%s\t|\t%s", E.date,E.time);

        // Edit line button

        gotoxy(bx2 + 8, 5);
        if(current == 'l') printf("\033[1;34mEdit\033[0m");
        else printf("Edit");
        
        // no need for gotoxy here
        //box
        if(current == 'c' )
        {
            glow_line(bx1,by1, bx2,by1);
            glow_line(bx2,by1,bx2,by2);
            glow_line(bx2,by2, bx1, by2);
            glow_line(bx1,by2,bx1,by1);
        }
        else 
        {
            line(bx1,by1, bx2,by1);
            line(bx2,by1,bx2,by2);
            line(bx2,by2, bx1, by2);
            line(bx1,by2,bx1,by1);
        }

        if(current == 's' && E.favourite == 0) 
        {
            gotoxy(star_x, star_y);
            printf("\033[1;34mStarMark\033[0m\n");
        }
        else if(E.favourite == 1)
        {
            gotoxy(star_x, star_y);
            printf("\033[1;33mStarMark\033[0m\n"); // yellow for star
        }
        else
        {
            gotoxy(star_x, star_y);
            printf("StarMark");
        }

        
}

void getContent(char str[])
{
    int index = 0;

    // Read input character by character
    while (1) {
        char c = getchar();

        // Exit loop if '*' is pressed
        if (c == '*') {
            break;
        }

        // If Enter is pressed, add a newline and a tab
        if (c == '\n') {
            printf("\033[1;34m.\033[0m");
            putchar(' ');
            str[index++] = c;
            str[index++] = ' ';
            str[index++] = ' ';
        }
        // Otherwise, append the character to the string and print it
        else {
            //putchar(c);
            str[index++] = c;
        }
    }

    // Null-terminate the string
    str[index] = '\0';
}

void NewEntry(int last_index)
{   
   //initialising block
    entry E;
    E.favourite =0; // initially
    E.index = last_index + 1;
    E.date = getCurrentDate();
    E.time = getCurrentTime();
    strcpy(E.topic,"");
    strcpy(E.content,"");

    //current_block
    char current = 't';
    // t ->topic
    // c -> content
    // s -> star
    // l - > line edit
    // e -> save and exit
    
    int done =0;

   //starts
   while(1)
   {
        drawEditor(current,E);
        char choice = getche();
        switch(choice)
        {

            case 72:// for up arrow key
            {
                if(current == 'c')
                {
                    current = 't';
                }

                if(current == 's')
                {
                    current = 'c';
                }
                
                if(current == 'l')
                {
                    current = 'e';
                }
                break;
            }


            case 80://for down arrow key
            {
                if(current == 't')
                {
                    current = 'c';
                }

                else if(current == 'c')
                {
                    current = 's';
                }

                if(current == 'e')
                {
                    current = 'l';
                }
                
                break;
            }

            case 77://for right arrow key
            {
                if(current == 't')
                {
                    current = 'e';
                }

                if(current == 'c')
                {
                    current = 'l';
                }

                if(current == 's')
                {
                    current = 'l';
                }
                
                break;
            }


            case 75://for left arrow key
            {
                if(current == 'e')
                {
                    current = 't';
                }

                if(current == 'l')
                {
                    current = 'c';
                }

                if(current == 's')
                {
                    current = 'c';
                }
                
                break;
            }

            case '\r':
            {
                if(current == 's'  &&  E.favourite == 0)
                {
                    E.favourite = 1;
                    printf("favourite is: %d",E.favourite);
                }

                else if(current == 's'  &&  E.favourite == 1)
                {
                    E.favourite = 0;
                    printf("favourite is: %d",E.favourite);
                }
                
                else if(current == 't')
                {
                    gotoxy(48,0);
                    scanf("%[^\n]s",E.topic);
                    fflush(stdin);
                }

                else if(current == 'c')
                {
                    gotoxy(bx1+2,by1+1); // because u know, 2 space system
                    getContent(E.content);
                    fflush(stdin);
                }

                else if(current == 'e') // Save and Exit part
                {
                    done =1;
                }
                
                else if(current == 'l') // editing panel
                {
                    // gotoxy(0,0);
                    // printf("Enter Line: ");
                    // int line;
                    // scanf("%d", &line);
                    // fflush(stdin);
                    // current_line = line; // this makes the line blue
                    // gotoxy(0,0);
                    // printf("Enter Replacement: ");
                    // char rep[120];
                    // scanf("%[^\n]s",&rep);
                    // fflush(stdin);
                    // EditContent(rep,E.content);


//from here
                    current_line = 1;
                    int done =0;
                    current = 'c';

                    while(1)
                    {
                        drawEditor(current,E);
                        char blue = getche();
                        switch (blue)
                        {
                        case 80: // down
                        if(current_line< MaxLines(E.content) -1) 
                            current_line ++;
                            break;
                        
                        case 72: // up
                        if(current_line>1)
                            current_line --;
                            break;

                        case '\r': 
                        {
                            done =1;
                            
                            gotoxy(0,by2 +5); // will change this later
                            printf("Enter Replacement:");
                            char rep[120];
                            scanf("%[^\n]s", rep);
                            AddSpace(rep);
                            fflush(stdin);
                            EditContent(rep,E.content);
                            break;
                        }

                        }
                         if(done ==1) break;

                    }
                    
                    current_line = -1;
// till here
                }
                break;
            }

    }
    if(done == 1) break;
   }
    // main thing here
    system("cls");
     FILE * fp;
     fp = fopen(filename, "ab"); // better this is than using fseek
    // fseek(fp,0,SEEK_END);
    fwrite(&E,sizeof(E),1,fp);
    fclose(fp); // worked wonders
    printf("Saved Successfully");
    getchar();

}
