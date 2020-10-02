#include "headers.h"
#include "pipe.h"
#include "main.h"
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
    int tot = get_pipe_args(command);
    int type = 0, pipe_arr[2], fd = 0;
    pid_t npid;
    for (int j = 0; j < tot; j++)
    {
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
            exit(0);
        }
        else if (npid == -1)
        {
            perror("\x1B[1;31mError while forking \x1B[1;0m");
            prestat = 'f';
            return 1;
        }
        else
        {
            wait(NULL);
            close(pipe_arr[1]);
            fd = pipe_arr[0];
        }
    }
}
