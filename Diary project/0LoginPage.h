#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_userNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

typedef struct
{
    char username[MAX_userNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} user;
user currentuser;
char filename[25];

// Function to check if a username exists in the password file
int checkusernameExists(char *username)
{
    FILE *file = fopen("password.txt", "r");
    if (file == NULL)
    {
        return 0; // File doesn't exist, so username can't exist
    }

    char line[MAX_userNAME_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, username) != NULL)
        {
            fclose(file);
            return 1; // username found
        }
    }

    fclose(file);
    return 0; // username not found
}

// Function to register a new user
void registeruser()
{
    user user;
    char confirm[MAX_PASSWORD_LENGTH];

    printf("\x1b[33mEnter a username: \x1b[0m");
    scanf("%s", user.username);

    if (checkusernameExists(user.username))
    {
        printf("\x1b[31musername already exists. Please choose another.\x1b[0m\n");
        return;
    }

    printf("Enter a password: ");
    scanf("%s", user.password);

    printf("Confirm password: ");
    scanf("%s", confirm);

    if (strcmp(user.password, confirm) != 0)
    {
        printf("\x1b[31mPasswords do not match. Registration failed.\x1b[0m\n");
        return;
    }

    FILE *file = fopen("password.txt", "a");
    if (file == NULL)
    {
        printf("\x1b[31mError opening file.\x1b[0m\n");
        return;
    }

    fprintf(file, "%s %s\n", user.username, user.password);
    fclose(file);

    // Create a text file for the user
    // char filename[MAX_userNAME_LENGTH + 5];
    // snprintf(filename, sizeof(filename), "%s.txt", user.username);
    strcpy(filename, user.username);
    strcat(filename, ".exe");
    printf("\nyour filename is %s", filename);
    FILE *userFile = fopen(filename, "wb");
    if (userFile == NULL)
    {
        printf("\x1b[31mError creating user file.\x1b[0m\n");
        return;
    }

    fclose(userFile);
    printf("\n\x1b[32mRegistration successful.\x1b[0m\n");
    return;
}

// Function to authenticate a user
int login(user *user)
{
    FILE *file = fopen("password.txt", "r");
    if (file == NULL)
    {
        printf("\x1b[31mError opening file.\x1b[0m\n");
        return 0;
    }

    char line[MAX_userNAME_LENGTH + MAX_PASSWORD_LENGTH + 2]; // +2 for space and newline
    while (fgets(line, sizeof(line), file))
    {
        char savedusername[MAX_userNAME_LENGTH];
        char savedPassword[MAX_PASSWORD_LENGTH];
        sscanf(line, "%s %s", savedusername, savedPassword);

        if (strcmp(user->username, savedusername) == 0 && strcmp(user->password, savedPassword) == 0)
        {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication failed
}

void LoginPage()
{
    int choice;
    user currentuser;

    do
    {
        printf("\x1b[33m1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\x1b[0m\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registeruser();
            break;
        case 2:
            printf("\x1b[33mEnter your username: \x1b[0m");
            scanf("%s", currentuser.username);

            printf("\x1b[33mEnter your password: \x1b[0m");
            scanf("%s", currentuser.password);

            if (login(&currentuser))
            {
                strcpy(filename, currentuser.username);
                strcat(filename, ".exe");
                printf("\nyour filename is %s\n", filename);
                printf("\x1b[32mLogin successful.\x1b[0m\n");
                printf("\x1b[Press ENTER to continue.\x1b[0m\n");
                getchar();
                getchar();
                return;
            }
            else
            {
                printf("\x1b[31mIncorrect username or password.\x1b[0m\n");
                // printf("\x1b[Press ENTER to continue.\x1b[0m\n");
                // getchar();
                return ;
                return;
            }
            break;
        case 3:
            printf("Exiting...\n");
            exit(0);
        default:
            printf("\x1b[31mInvalid choice. Please try again.\x1b[0m\n");
        }
    } while (1);

    return;
}