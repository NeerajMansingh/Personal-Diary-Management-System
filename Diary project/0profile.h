#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int indexnum=1;

struct userprofile
{
    int indexnum;
    char username[20];
    char email[50];
    int age;
    char fieldofinterest[100];
};

void saveUserProfile(struct userprofile user)
{
    FILE *file = fopen(filename, "ab+");
    fseek(file, 0, SEEK_END); // I ENT THE ENTRY IT SAVE AT THE END
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&user, sizeof(user), 1, file);
    // fprintf(file, "%s,%s,%d,%s\n", user.username, user.email, user.age, user.fieldofinterest);
    system("cls");
    getchar();
    fclose(file);
}

void readfile()
{
    FILE *fptr1 = NULL;
    fptr1 = fopen(filename, "rb");
    if (fptr1 == NULL)
    {
        printf("File not opened\n");
        return;
    }
    struct userprofile details;
    while (fread(&details, sizeof(details), 1, fptr1))
    {
        system("cls");
        printf("\033[1;31mUSER NUMBER:\033[0m %d\n",details.indexnum);
        printf("\033[1;31mUsername is:\033[0m %s\n", details.username);
        printf("\033[1;31mYour email ID is:\033[0m %s\n", details.email);
        printf("\033[1;31mYour age is:\033[0m %d\n", details.age);
        printf("\033[1;31mYour field of interests are:\033[0m %s\n", details.fieldofinterest);
        printf("Press Enter to continue");
        // getchar();
        getchar();
        // system("cls");
        indexnum++;
    }
    fclose(fptr1);
}


void ProfilePage()
{
    int choice;
    struct userprofile user;

    while (1)
    {
       
        printf("\033[1;32m1. Create User Profile..\033[0m\n");
        printf("\033[1;32m2. View User Profiles..\033[0m\n");
        printf("\033[1;32m3. Exit\033[0m\n");
        printf("Enter your choice:\n ");
        scanf("%d", &choice);
        // getchar();
        fflush(stdin);
        switch (choice)
        {
        case 1:
        //indexnum++;
        system("cls");
        getchar();
            printf("\033[1;36menter the username:\033[0m\n");
            scanf("%[^\n]s",user.username);
            printf("\033[1;36mEnter email:\033[0m\n ");
            scanf("%s",user.email);
            printf("\033[1;36mEnter age:\033[0m\n ");
            scanf("%d",&user.age);
            printf("\033[1;36mEnter field of interest:\033[0m\n ");
            getchar();
            scanf("%[^\n]s",user.fieldofinterest);
            user.indexnum=indexnum;
            saveUserProfile(user);
            indexnum++;
            break;

        case 2:
            readfile();
            getchar();
            break;

        case 3:
            printf("exit the programm..\n");
            exit(0);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return ;
}