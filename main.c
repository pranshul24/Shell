#include "prompt.h"
#include "headers.h"
#include "changedir.h"
#include "ls.h"
#include "echo.h"
#include "pwd.h"
#include "pinfo.h"
#include "run.h"
#include "history.h"
#include "nightswatch.h"
#include "handle_env.h"
#include "manage_jobs.h"
#include "bg.h"
#include "overkill.h"
#include "fg.h"
#define ll long long
ll k = 1;
size_t sz = 1010;
char colonsep[100][1000];
long long sep(char *str)
{
    char *ptrs = strtok(str, ";");
    long long i = 0;
    while (ptrs != NULL)
    {
        strcpy(colonsep[i], ptrs);
        i++;
        ptrs = strtok(NULL, ";");
    }
    return i;
}
void call_command(char *stringy)
{
    long long countsep = sep(stringy);
    char *copy_ptr = (char *)malloc(sizeof(char) * 2000);
    char *copy_ptr2 = (char *)malloc(sizeof(char) * 2000);
    long long ii = 0;
    while (ii < countsep)
    {
        long long i;
        strcpy(copy_ptr, colonsep[ii]);
        strcpy(copy_ptr2, colonsep[ii]);
        char *ptrs2 = strtok(copy_ptr2, " \t");
        char *command = (char *)malloc(sz * sizeof(char));
        char *argument = (char *)malloc(sz * sizeof(char));
        if (ptrs2 == NULL)
        {
            ii++;
            continue;
        }
        else
        {
            write_his(copy_ptr);
            strcpy(command, ptrs2);
            ptrs2 = strtok(NULL, "");
            if (ptrs2 == NULL)
            {
                argument = NULL;
            }
            else
            {
                strcpy(argument, ptrs2);
            }
        }
        if (strcmp(command, "cd") == 0)
        {
            cd(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "ls") == 0)
        {
            ls(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "echo") == 0)
        {
            echo(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "nightswatch") == 0)
        {
            nwatch(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "pwd") == 0)
        {
            pwd(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "pinfo") == 0)
        {
            pinfo(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "quit") == 0)
        {
            printf("\n\t\t\t\t\t\x1B[1;35mGoodBye ! Hopefully see you again !\n\n");
            exit(0);
        }
        else if (strcmp(command, "history") == 0)
        {
            history(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "setenv") == 0)
        {
            set_env_var(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "jobs") == 0)
        {
            print_jobs(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "kjob") == 0)
        {
            kjob(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "bg") == 0)
        {
            bg(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "fg") == 0)
        {
            fg(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "overkill") == 0)
        {
            kill_all_backg(argument);
            ii++;
            continue;
        }
        else if (strcmp(command, "unsetenv") == 0)
        {
            unset_env_var(argument);
            ii++;
            continue;
        }
        else
        {
            run(copy_ptr, 0);
            rewrite_his();
        }
        ii++;
    }
}
int main()
{
    total_back_process = 0;
    getcwd(home, sz - 5);
    strcpy(hist_filename, home);
    strcat(hist_filename, "/history_store.txt");
    hist_cnt = get_count_his();
    printf("\033[H\033[J");
    printf("\t\t\t\t\t\x1B[1;35mHey ! Welcome to PC's Shell !\n\n");
    while (k)
    {
        char *str = (char *)malloc(sz * sizeof(char));
        prompt_stdout(home);
        getline(&str, &sz, stdin);
        str[strlen(str) - 1] = '\0';
        if (str != NULL)
        {
            call_command(str);
        }
    }
}
