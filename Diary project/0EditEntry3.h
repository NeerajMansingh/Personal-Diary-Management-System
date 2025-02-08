#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define bx1 0
#define bx2 100
#define by1 4
#define by2 20
#define star_x 60
#define star_y by2 +2
// current_line =0; // global variable

// #include "0EditContent.h" //vvimp

void ViewEntry(int idx)
{   
   //initialising block
    entry E;
    E.favourite =0; // initially
    E.index = idx;
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
     FILE * fp= fopen(filename, "rb+");
    //find entry
    while(fread(&E,sizeof(E),1,fp)!=0)
    {
        if(E.index == idx)
        {
            break;
        }
    }

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
    //  FILE * fp= fopen(filename, "rb+"); // better this is than using fseek
    while(fread(&E,sizeof(E),1,fp)!=0)
    {
        if(E.index == idx)
        {
            break;
        }
    }
    fseek(fp,-sizeof(E),SEEK_END);
    fwrite(&E,sizeof(E),1,fp);
    fclose(fp); // worked wonders
    printf("Saved Successfully");
    getchar();

}
