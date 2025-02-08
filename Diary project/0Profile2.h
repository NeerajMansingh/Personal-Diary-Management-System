#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int indexnum = 1;

char arr1[50];

struct userprofile
{
    int indexnum;
    char username[20];
    char email[50];
    int age;
    char fieldofinterest[100];
};

void saveUserProfile(struct userprofile user1)
{
    struct userprofile details;
    FILE *fptr1 = fopen("profile.exe", "rb+");
    rewind(fptr1);

    int found = 0;
    while (fread(&details, sizeof(details), 1, fptr1))
    {
        if (strcmp(details.username, arr1) == 0)
        {

            fseek(fptr1, -sizeof(details), SEEK_CUR); // Move the file pointer back
            fwrite(&user1, sizeof(user1), 1, fptr1);  // Overwrite existing content
            found = 1;
            fclose(fptr1);
            // fprintf(file, "%s,%s,%d,%s\n", user.username, user.email, user.age, user.fieldofinterest);
            system("cls");
            getchar();

            break;
        }
    }

    if (found == 0)
    {
        {
            fseek(fptr1, 0, SEEK_END); // I ENT THE ENTRY IT SAVE AT THE END
            fwrite(&user1, sizeof(user1), 1, fptr1);
            // fprintf(file, "%s,%s,%d,%s\n", user.username, user.email, user.age, user.fieldofinterest);
            system("cls");
            getchar();
            fclose(fptr1);
        }
    }
}

void readfile()
{
    struct userprofile details;
    FILE *fptr1 = NULL;
    fptr1 = fopen("profile.exe", "rb");
    if (fptr1 == NULL)
    {
        printf("File not opened\n");
        return;
    }

    while (fread(&details, sizeof(details), 1, fptr1))
    {
        system("cls");
        if (strcmp(details.username, arr1) == 0)
        {
            // printf("\033[1;31mUSER NUMBER:\033[0m %d\n", details.indexnum);
            printf("\033[1;31mUsername is:\033[0m %s\n", details.username);
            printf("\033[1;31mYour email ID is:\033[0m %s\n", details.email);
            printf("\033[1;31mYour age is:\033[0m %d\n", details.age);
            printf("\033[1;31mYour field of interests are:\033[0m %s\n", details.fieldofinterest);
            printf("Press Enter to continue");
            // getchar();
            getchar();
        }
        system("cls");
        indexnum++;
    }
    fclose(fptr1);
}

void updateinfo()
{
    system("cls");
    struct userprofile user1;

    // printf("\033[1;36menter the username:\033[0m\n");
    // scanf("%[^\n]s", user.username);
    strcpy(user1.username, arr1);
    printf("\033[1;36mEnter email:\033[0m\n ");
    scanf("%s", user1.email);
    printf("\033[1;36mEnter age:\033[0m\n ");
    scanf("%d", &user1.age);
    printf("\033[1;36mEnter field of interest:\033[0m\n ");
    getchar();
    scanf("%[^\n]s", user1.fieldofinterest);
    user1.indexnum = indexnum;
    saveUserProfile(user1);
    indexnum++;
}



void ProfilePage()
{
    int choice;
    int counter = 0;
    while (filename[counter] != '.')
    {
        arr1[counter] = filename[counter];
        counter++;
    }
    arr1[counter] = '\0';
    // printf("\n%s\n",arr1);

    while (1)
    {
        system("cls");
        printf("\033[1;32m1. Update Profile...\033[0m\n");
        printf("\033[1;32m2. View User Profile...\033[0m\n");
        printf("\033[1;32m3. Exit\033[0m\n");
        printf("Enter your choice:\n ");
        scanf("%d", &choice);
        // getchar();
        fflush(stdin);
        switch (choice)
        {
        case 1:
            // indexnum++;
            updateinfo();
            break;

        case 2:
            readfile();
            getchar();
            break;

        case 3:
            return;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return;
}