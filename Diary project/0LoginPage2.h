 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "0gotoxy.h"

typedef struct
{
    char username[20];
    char password[50];
} User; // Change variable name to avoid conflict with type name

// char filename[25];

// check if a username exists in the password file
int userexists(char *username)
{
    FILE *file = fopen("password.txt", "r");
    if (file == NULL)
    {
        return 0; // user does not exist
    }

    char line[20];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, username) != NULL)
        {
            fclose(file);
            return 1; // user exists
        }
    }

    fclose(file);
    return 0; // user does not exist
}

// register a new user
void registeruser()
{
    User newUser; // Change variable name to avoid conflict with type name
    char confirm[50];
    system("cls"); // Clear screen before registering

    gotoxy(55, 5);
    printf("\x1b[33mEnter a username: \x1b[0m");
    scanf("%s", newUser.username);

    if (userexists(newUser.username))
    {
        gotoxy(50, 7);
        printf("\x1b[31mUsername already exists. Please choose another.\x1b[0m\n");
        getchar();
        getchar();
        return;
    }

    gotoxy(55, 7);
    printf("Enter a password: ");
    scanf("%s", newUser.password);
    gotoxy(55, 9);
    printf("Confirm password: ");
    scanf("%s", confirm);

    if (strcmp(newUser.password, confirm) != 0)
    {
        gotoxy(55, 11);
        printf("\x1b[31mPasswords do not match.\x1b[0m");
        gotoxy(55, 12);
        printf("\x1b[31mRegistration failed.\x1b[0m\n");
        getchar();
        getchar();
        return;
    }

    FILE *file = fopen("password.txt", "a");
    if (file == NULL)
    {
        gotoxy(55, 13);
        printf("\x1b[31mError opening file.\x1b[0m\n");
        return;
    }

    fprintf(file, "%s %s\n", newUser.username, newUser.password);
    fclose(file);
    strcpy(filename, newUser.username);
    strcat(filename, ".exe");

    FILE *userFile = fopen(filename, "wb");
    if (userFile == NULL)
    {
        gotoxy(55, 13);
        printf("\x1b[31mError creating user file.\x1b[0m\n");
        getchar();
        getchar();
        return;
    }

    fclose(userFile);
    gotoxy(55, 18);
    printf("\n\n\x1b[32mRegistration successful.\x1b[0m\n");
    getchar();
    getchar();

}

// login a user
int login(User *user)
{
    FILE *file = fopen("password.txt", "r");
    if (file == NULL)
    {
        gotoxy(55, 13);
        printf("\x1b[31mError opening file.\x1b[0m\n");
        return 0; // login failed
    }

    char line[72];
    while (fgets(line, sizeof(line), file))
    {
        char savedusername[20];
        char savedPassword[50];
        sscanf(line, "%s %s", savedusername, savedPassword);

        if (strcmp(user->username, savedusername) == 0 && strcmp(user->password, savedPassword) == 0)
        {
            fclose(file);
            return 1; // login successful
        }
    }

    fclose(file);
    return 0; // login failed
}

void LoginPage()
{
    int choice;
    User currentuser; // Change variable name to avoid conflict with type name

    while (1)
    {
        system("cls");
        gotoxy(59, 5);
        printf("\x1b[33m1. Register\n");
        gotoxy(59, 8);
        printf("2. Login\n");
        gotoxy(59, 11);
        printf("3. Exit\x1b[0m\n");
        gotoxy(55, 14);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registeruser();
            break;
        case 2:
            while (1)
            {
                system("cls");
                gotoxy(0, 0);
                printdate();
                gotoxy(0, 1);
                printtime();
                
                gotoxy(55, 5);
                printf("\x1b[33mEnter your username: \x1b[0m");
                scanf("%s", currentuser.username);
                gotoxy(55, 7);
                printf("\x1b[33mEnter your password: \x1b[0m");
                scanf("%s", currentuser.password);

                if (login(&currentuser))
                {
                    strcpy(filename, currentuser.username);
                    strcat(filename, ".exe");
                    gotoxy(55, 10);
                    printf("\x1b[32mLogin successful.\x1b[0m");
                    gotoxy(50, 11);
                    printf("\x1b[33mPress ENTER to continue.\x1b[0m");
                    while (getchar() != '\n')
                        ;
                    getchar();
                    return;
                }
                else
                {
                    gotoxy(55, 10);
                    printf("\x1b[31mIncorrect username or password.\x1b[0m\n");
                    gotoxy(50, 11);
                    printf("\x1b[33mDo you want to try again? (1 for Yes, 0 for No): \x1b[0m");
                    scanf("%d", &choice);

                    if (choice == 0)
                    {
                        break;
                    }
                }
            }
            break;
        case 3:
            system("cls");
            gotoxy(55, 8);
            printf("Exiting...\n");
            exit(0);
        default:
            gotoxy(55, 13);
            printf("\x1b[31mInvalid choice. Please try again.\x1b[0m\n");
            getchar();
            getchar();
        }
    }
}
