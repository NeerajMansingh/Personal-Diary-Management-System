#include <time.h>
#include <stdio.h>
void printdate(){
    time_t rawtime;
    struct tm *info;
    char datebuffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(datebuffer,sizeof(datebuffer),"%d-%m-%Y",info);
    printf(datebuffer);
}
void printtime(){
    time_t rawtime;
    struct tm *info;
    char timebuffer[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(timebuffer,sizeof(timebuffer),"%H:%M",info);
    printf(timebuffer);
}