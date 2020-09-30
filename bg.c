#include "headers.h"
#include "bg.h"
void bg(char *argu)
{
    int jobn;
    char *ptr = (char *)malloc(sizeof(char) * 2000);
    ptr = strtok(argu, " \t");
    char fst[105];
    if (ptr != NULL)
    {
        strcpy(fst, ptr);
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
        jobn = atoi(fst);
        if (jobn == 0 || jobn > total_back_process)
        {
            printf("\x1B[1;31mError : enter job number correctly !!!\x1B[0m\n");
            prestat = 'f';
            return;
        }
        else
        {
            kill(pid_arr[jobn - 1], SIGCONT);
        }
    }
}