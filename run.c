#include "headers.h"
#include "run.h"
#include "prompt.h"

char err_string[200];
void print_err(char *str)
{
    perror(str);
}
void print_status(char *str2)
{
    fprintf(stderr, "%s", str2);
}
void manage_pid_arr(int rempid)
{
    int i;
    for (i = 0; i < total_back_process; i++)
    {
        if (pid_arr[i] == rempid)
        {
            break;
        }
    }
    for (int j = i; j < total_back_process - 1; j++)
    {
        pid_arr[j] = pid_arr[j + 1];
    }
}

void run(char *args, int back_g)
{
    char *arr_string4[101];
    int h = strlen(args), i;
    for (i = 0; i < h; i++)
    {
        if (args[i] != ' ')
            break;
    }
    char *ptr = (char *)malloc(sizeof(char) * 1000);
    ptr = strtok(args + i, " \t");
    long long len = 0;
    while (ptr != NULL)
    {
        arr_string4[len] = ptr;
        len++;
        ptr = strtok(NULL, " \t");
    }
    arr_string4[len] = NULL;
    int flagc = 0;
    if (strcmp(arr_string4[len - 1], "&") == 0 || (arr_string4[len - 1][strlen(arr_string4[len - 1]) - 1] == '&'))
    {
        back_g = 1;
        if (strcmp(arr_string4[len - 1], "&") == 0)
        {
            arr_string4[len - 1] = NULL;
            flagc = 1;
        }
        else
        {
            arr_string4[len - 1][strlen(arr_string4[len - 1]) - 1] = '\0';
        }
    }
    if (back_g == 0)
    {
        int status;
        pid_t pid = fork(), wpid;
        if (pid == 0) // for CHILD
        {
            setpgid(0, 0);
            if (execvp(arr_string4[0], arr_string4) != 0)
            {
                printf("\x1B[1;31mSorry!!! I don't know this command\n\x1B[0m");
                prestat = 'f';
                exit(1);
            }
            else
            {
                exit(0);
            }
        }
        else if (pid == -1)
        {
            strcpy(err_string, "\x1B[1;31mSorry !!! :\x1B[0m");
            prestat = 'f';
            print_err(err_string);
            return;
        }
        else if (pid >= 1)
        {
            fg_pid = pid;
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            setpgid(pid, 0);
            tcsetpgrp(0, pid);
            waitpid(pid, &status, WUNTRACED);
            tcsetpgrp(0, getpgrp());
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
            if (WIFSTOPPED(status))
            {
                int i = 0;
                if (len > 0)
                {
                    strcpy(process_name[pid], arr_string4[i]);
                    i++;
                }
                while (i < len - 1)
                {
                    strcat(process_name[pid], " ");
                    strcat(process_name[pid], arr_string4[i]);
                    i++;
                }
                if (flagc == 0 && len > 1)
                {
                    strcat(process_name[pid], " ");
                    strcat(process_name[pid], arr_string4[i]);
                }
                printf("\x1B[1;36m\n[%d] %s with PID [%d] suspended\n\x1B[0m", total_back_process + 1, process_name[pid], pid);
                prestat = 'f';
                pid_arr[total_back_process] = pid;
                total_back_process++;
            }
            fg_pid = -1;
            if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
            {
                prestat = 'f';
            }
            return;
        }
    }
    else if (back_g == 1)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            strcpy(err_string, "\x1B[1;31mError \x1B[0m");
            print_err(err_string);
            prestat = 'f';
            exit(1);
        }
        else if (pid == 0) // for CHILD
        {
            setpgid(0, 0);
            if (execvp(arr_string4[0], arr_string4) == -1)
            {
                strcpy(err_string, "\x1B[1;31mCould not execute command\x1B[0m");
                print_err(err_string);
                exit(1);
            }
        }
        else if (pid >= 1)
        {
            pid_arr[total_back_process] = pid;
            total_back_process++;
            printf("\x1B[1;36m[%d] %d\x1B[0m\n", total_back_process, pid);
            int i = 0;
            if (len > 0)
            {
                strcpy(process_name[pid], arr_string4[i]);
                i++;
            }
            while (i < len - 1)
            {
                strcat(process_name[pid], " ");
                strcat(process_name[pid], arr_string4[i]);
                i++;
            }
            if (flagc == 0 && len > 1)
            {
                strcat(process_name[pid], " ");
                strcat(process_name[pid], arr_string4[i]);
            }
            setpgid(pid, 0);
            tcsetpgrp(0, getpgrp());
            return;
        }
    }
    return;
}