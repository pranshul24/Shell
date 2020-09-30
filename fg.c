#include "headers.h"
#include "fg.h"
void fg(char *argu)
{
    char *ptr = (char *)malloc(sizeof(char) * 1000);
    int pd, jobn, status;
    ptr = strtok(argu, " \t");
    char fst[205];
    if (ptr != NULL)
    {
        strcpy(fst, ptr);
        jobn = atoi(fst);
    }
    long long k = 0;
    while (ptr != NULL)
    {
        k++;
        ptr = strtok(NULL, " \t");
        if (k > 1)
        {
            break;
        }
    }
    if (k == 0 || k > 1)
    {
        printf("\x1B[1;31mError : enter arguments correctly !!!\x1B[0m\n");
        prestat = 'f';
        return;
    }
    else if (k == 1)
    {
        if (jobn == 0 || jobn > total_back_process)
        {
            printf("\x1B[1;31mError : enter job number correctly !!!\x1B[0m\n");
            prestat = 'f';
            return;
        }
        else
        {
            pd = pid_arr[jobn - 1];
            fg_pid = pd;
            char *pname = (char *)malloc(1000 * sizeof(char));
            strcpy(pname, process_name[pd]);
            int i;
            for (i = 0; i < total_back_process; i++)
            {
                if (pid_arr[i] == pd)
                {
                    break;
                }
            }
            for (int j = i; j < total_back_process - 1; j++)
            {
                pid_arr[j] = pid_arr[j + 1];
            }
            total_back_process--;
            signal(SIGTTOU, SIG_IGN);
            signal(SIGTTIN, SIG_IGN);
            tcsetpgrp(0, pd);
            kill(pd, SIGCONT);
            waitpid(pd, &status, WUNTRACED);
            tcsetpgrp(0, getpgrp());
            signal(SIGTTOU, SIG_DFL);
            signal(SIGTTIN, SIG_DFL);
            if (WIFSTOPPED(status))
            {
                printf("\x1B[1;36m[%d] %s with PID [%d] suspended\n\x1B[0m", total_back_process + 1, process_name[pd], pd);
                pid_arr[total_back_process] = pd;
                total_back_process++;
                prestat = 'f';
            }
            if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
            {
                prestat = 'f';
            }
            fg_pid = -1;
        }
    }
    return;
}