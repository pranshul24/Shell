#include "headers.h"
#include "overkill.h"
void kill_all_backg(char *argu)
{
    char *ptr = (char *)malloc(sizeof(char) * 2000);
    ptr = strtok(argu, " \t");
    if (ptr != NULL)
    {
        printf("\x1B[1;31mError : can't enter arguments with overkill command !!!\x1B[0m\n");
        prestat = 'f';
        return;
    }
    else if (ptr == NULL)
    {
        if (total_back_process == 0)
        {
            printf("\x1B[1;31mAlready no background process !!!\x1B[0m\n");
            return;
        }
        else if (total_back_process >= 1)
        {
            for (int i = 0; i < total_back_process; i++)
            {
                kill(pid_arr[i], SIGKILL);
            }
        }
    }
    return;
}