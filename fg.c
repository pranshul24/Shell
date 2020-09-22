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
        return;
    }
    else if (k == 1)
    {
        if (jobn == 0 || jobn > total_back_process)
        {
            printf("\x1B[1;31mError : enter job number correctly !!!\x1B[0m\n");
            return;
        }
        else
        {
            pd = pid_arr[jobn - 1];
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
            kill(pd, SIGCONT);
            waitpid(pd, &status, WUNTRACED);
        }
    }
    return;
}