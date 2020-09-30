#include "headers.h"
#include "pipe.h"
#include "main.h"
int pipe_elements(char *input)
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
    int tot = pipe_elements(command);
    int type = 0, parr[2], fd = 0;
    pid_t newproc;

    for (int j = 0; j < tot; j++)
    {
        pipe(parr);
        newproc = fork();
        if (newproc == 0)
        {
            dup2(fd, 0);
            if (j + 1 < tot)
                dup2(parr[1], 1);
            close(parr[0]);
            strcpy(colonsep[0], pipe_args[j]);
            call_command(1, 1);
            exit(2);
        }
        else if (newproc <= -1)
        {
            perror("Could not create child.");
            prestat = 'f';
            exit(1);
        }
        else
        {
            wait(NULL);
            close(parr[1]);
            fd = parr[0];
        }
    }
}
