/* File name:   shell-9221.c
   Descripption: a sample program that is used as a shell.
   Compile: gcc -o shell shell-9221.c
   Run: ./shell
*/
#define _POSIX_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/wait.h>

void GetLogin()
{
    uid_t uid;
    printf("\n%d: ", uid = getuid());
}
void PrintError(char *argv[10])
{
    int i = 0;
    printf("Error: ");
    while (argv[i] != NULL)
    {
        printf("%s ", argv[i]);
        i++;
    }
}

void ExecuteCommand(char *argv[])
{
    int status;
    pid_t Cpid = fork();
    if (Cpid < 0)
    {
        printf("Error Fork Failed");
        exit(1);
    }
    else if (Cpid == 0)
    {
        execvp(argv[0], argv);
        PrintError(argv);
        exit(1);
    }
    else
    {
        waitpid(Cpid, &status, 0);
    }
}

void Shell()
{
    char input[100];
    char *argv[10];
    while (1)
    {
        GetLogin();
        fgets(input, 50, stdin);
        int i = 0;
        char *token = strtok(input, " \n");
        while (token)
        {
            argv[i] = token;
            i++;
            token = strtok(NULL, "\n");
        }
        argv[i] = NULL;
        if (strcmp(argv[0], "cd") == 0 || strcmp(argv[0], "chdir") == 0)
        {
            chdir(argv[1]);
        }
        else if (strcmp(argv[0], "exit") == 0)
        {
            exit(0);
        }
        else
        {
            ExecuteCommand(argv);
        }
    }
}

int main()
{
    Shell();
}