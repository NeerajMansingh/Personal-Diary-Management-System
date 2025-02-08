#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *task;
    int completed; // 1 for true 0 for false
} Task;

Task *tasks = NULL;
int length = 0;

void addTask(const char *task)
{
    tasks = (Task *)realloc(tasks, (length + 1) * sizeof(Task));
    tasks[length].task = (char *)malloc(strlen(task) + 1);
    tasks[length].completed = 0;
    strcpy(tasks[length].task, task);
    length++;
    printf("\033[0;32mtask added\033[0m\n"); // Green color for success message
    getchar();
}

void listTask()
{
    char status;
    for (int i = 0; i < length; i++)
    {
        status = tasks[i].completed == 1 ? 'd' : 'n';
        printf("%d. %s[%c]\n", i + 1, tasks[i].task, status);
        // getchar();
    }

        getchar();
}

void markcompleted(int index)
{
    if (index <= length && index > 0)
    {
        tasks[index - 1].completed = 1;
        printf("\033[0;32mTASK MARKED AS COMPLETED...\033[0m\n"); // Green color for success message
        getchar();
    }
    else
    {
        printf("\033[0;31mINVALID INDEX\033[0m\n"); // Red color for error message
    }
}

void deleteTask(int index)
{
    if (index <= length && index > 0)
    {
        index = index - 1;

        free(tasks[index].task);
        for (int i = index; i < length - 1; i++)
        {
            tasks[i] = tasks[i + 1];
        }
        length--;
        tasks = (Task *)realloc(tasks, length * sizeof(Task));
    }
    else
    {
        printf("\033[0;31mINVALID INDEX\033[0m\n"); // Red color for error message
    }
}

void editTask(int index, const char *task)
{
    if (index <= length && index > 0)
    {
        index = index - 1;
        char *editedtask = (char *)realloc(tasks[index].task, strlen(task) + 1);
        if (editedtask != NULL)
        {
            tasks[index].task = editedtask;
            strcpy(tasks[index].task, task);
            printf("\033[0;32mTask update successfully\033[0m\n"); // Green color for success message
            getchar();
        }
        else
        {
            printf("\033[0;31mmemory allocation failed\033[0m\n"); // Red color for error message
        }
    }
    else
    {
        printf("\033[0;31minvalid index\033[0m\n"); // Red color for error message
    }
}

void ToDoList()
{
    int choice;
    int running = 1;
    char taskInput[100];
    int indexInput;

    while (running)
    {
        system("cls");
        printf("\033[0;36m\n Options ..\n");
        printf(" 1. Add a task\n");
        printf(" 2. List all tasks\n");
        printf(" 3. Mark as completed\n");
        printf(" 4. Edit the task\n");
        printf(" 5. Delete the task\n");
        printf(" 6. Exit\n\033[0m");                   // blue color for menu options
        printf("\033[0;36menter the choice: \033[0m"); // Cyan color for user input prompt
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\033[0;36menter task: \033[0m");

            getchar(); // Clear input buffer
            fgets(taskInput, sizeof(taskInput), stdin);
            taskInput[strcspn(taskInput, "\n")] = '\0';
            addTask(taskInput);
            break;

        case 2:
            listTask();
            getchar();
            break;

        case 3:
            listTask();
            fflush(stdin);
            printf("\033[0;36menter index: \033[0m");
            scanf("%d", &indexInput);
            markcompleted(indexInput);
            getchar();
            break;

        case 4:
            listTask();
            fflush(stdin);
            printf("\033[0;36menter index: \033[0m");
            scanf("%d", &indexInput);
            printf("\033[0;36menter edited text: \033[0m");
            getchar(); 
            fgets(taskInput, sizeof(taskInput), stdin);
            taskInput[strcspn(taskInput, "\n")] = '\0';
            editTask(indexInput, taskInput);
            break;
        case 5:
            listTask();
            fflush(stdin);
            printf("\033[0;36menter index: \033[0m");
            scanf("%d", &indexInput);
            deleteTask(indexInput);
            getchar();
            break;

        case 6:
            running = 0;
            break;

        default:
            printf("\033[0;31minvalid choice\033[0m\n"); // Red color for error message
            getchar();
            // system("cls");
        }
    }

    // Free allocated memory
    for (int i = 0; i < length; i++)
    {
        free(tasks[i].task);
    }
    free(tasks);

    return;
}
