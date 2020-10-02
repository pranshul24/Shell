#include "headers.h"
#include "pipe.h"
#include "main.h"
int get_tot_pipes(char *input)
{
    int no = 0, i, n = strlen(input);
    for (i = 0; i < n; i++)
    {
        if (input[i] == '|')
        {
            no++;
        }
    }
    return no;
}
int get_pipe_args(char *input)
{
    char *p = strtok(input, "|");
    no = 0;
    while (p != NULL)
    {
        strcpy(pipe_args[no], p);
        no++;
        p = strtok(NULL, "|");
    }
    return no;
}
int piping(char *command)
{
    int tot2 = get_tot_pipes(command);
    int tot = get_pipe_args(command);
    char *ptr = (char *)malloc(1000 * sizeof(char));
    char *ptr2 = (char *)malloc(1000 * sizeof(char));
    if (tot2 + 1 != tot)
    {
        printf("\x1B[1;31mParsing error in pipe !!! \n\x1B[1;0m");
        prestat = 'f';
        return 1;
    }
    else if (tot2 + 1 == tot)
    {
        for (int i = 0; i < tot; i++)
        {
            strcpy(ptr, pipe_args[i]);
            ptr2 = strtok(ptr, " \t");
            if (ptr2 == NULL)
            {
                printf("\x1B[1;31mParsing error in pipe !!! \n\x1B[1;0m");
                prestat = 'f';
                return 1;
            }
        }
    }
    int type = 0, pipe_arr[2], fd = 0, status;
    pid_t npid;
    for (int j = 0; j < tot; j++)
    {
        prestat = 's';
        pipe(pipe_arr);
        npid = fork();
        if (npid == 0)
        {
            dup2(fd, 0);
            if (j + 1 < tot)
            {
                dup2(pipe_arr[1], 1);
            }
            close(pipe_arr[0]);
            strcpy(colonsep[0], pipe_args[j]);
            call_command(1, 1);
            if (prestat == 'f')
            {
                exit(1);
            }
            else if (prestat == 's')
            {
                exit(0);
            }
        }
        else if (npid == -1)
        {
            perror("\x1B[1;31mError while forking \x1B[1;0m");
            prestat = 'f';
            return 1;
        }
        else
        {
            waitpid(npid, &status, 0);
            if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0))
            {
                prestat = 'f';
            }
            close(pipe_arr[1]);
            fd = pipe_arr[0];
        }
    }
}
