#include <stdio.h>
#include <string.h>

// int current_line = 4; // for now

int CurrentLineLength(char str[]) // find len of current_line
{
    // printf("Im here toooo");
    int i =0;
    int line =1;
    int count = 0;
    while(str[i] != '\0')
    {
        if(str[i] == '\n') line ++;

        if(line == current_line)
        {
            if(str[i] != '\n') count++;
        }

        i++;
    }

    return count;
}
// char initial[] = "Hello\nThis\nIs \nA Nice\nString";

// char rep[] = "1234567890";

void EditContent(char rep[], char initial[])
{
    // printf("Im here");
    int len = strlen(rep);
    // now gotta find length of the required line
    int act_len = CurrentLineLength(initial);
    int diff = len - act_len;
    int final_len = strlen(initial) + diff;

    char final[final_len];
    // now a new content string has been created

    int i =0; // for initial
    int j =0; // for final
    int k =0;
    int line =1;
    //printf("\n %d %d %d \n", final_len, diff, act_len);

    while(i<strlen(initial))
    {
        // printf("%d", line);
        if(line !=  current_line)
        {
            final[j] = initial[i];
            i++;
            j++;
        }
        
        if(line == current_line)
        {
            final[j] = rep[k];
            j++;
            k++;
        }

        if(initial[i] == '\n')
        {
            i++;
            line++;
            final[j] = '\n';
            j++;
        }  // vvimp

        if(line == current_line  && k==len)
        {
            line++;
            i+= act_len ; // we want to skip that line now
        }

        
    }

    final[j] = '\0'; // to end string;

    strcpy(initial,final);
    // hopic that length of final is LESS than 2000
}