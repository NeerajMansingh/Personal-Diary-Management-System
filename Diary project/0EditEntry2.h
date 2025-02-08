#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// rest of functions are covered in 0NewEntry2.h

void ViewEntry(int idx)
{   //initialising block
    entry E;
    E.favourite =0; // initially
    E.index = idx; 
    if(E.index == 0) E.index =1;

    E.date = getCurrentDate();
    E.time = getCurrentTime();
    strcpy(E.topic,"");
    strcpy(E.content,"");

    // Opening file and Extracting
    system("cls");
     FILE * fp;
     fp = fopen(filename, "rb+"); // better this is than using fseek
    // fseek(fp,0,SEEK_END);
    
    while(fread(&E,sizeof(E), 1, fp) != 0)
    {
        if(E.index == idx)break;
    }

    system("cls");
    printf("Currently editing entry num %d", E.index);
    getchar();


    //current_block
    char current = 't';
    // t ->topic
    // c -> content
    // s -> star
    // l - > line edit
    // e -> save and exit
    // d -> delete entry
    // f -> fflush page
    
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
    printf("FInally, edited content is:%d,\n %s,\n %s\n ",E.index, E.topic, E.content);
    rewind(fp);
    printf("Current index = %d", E.index);
    getchar();

    while(fread(&E,sizeof(E),1,fp) !=0)
    {
        printf("Requited index is %d, and current index is %d",idx, E.index);
        if(E.index == idx)
        {
            printf("\n yay entry found");
            fseek(fp, -sizeof(E),SEEK_CUR);
            if (fwrite(&E,sizeof(E),1, fp) != 1) {
            printf("Error writing to file.\n");
        }
            break;
        }
    }
    getchar();
    
    fclose(fp);

}
