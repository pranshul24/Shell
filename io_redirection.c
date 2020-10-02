#include "headers.h"
#include "io_redirection.h"
#include "main.h"
int check_file(char *path)
{
    struct stat f;
    if (stat(path, &f) == 0 && S_ISDIR(f.st_mode) == 0) //exists and not a directory
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
int create_if_not(char *str, int type)
{
    int fd;
    if (type == 2)
    {
        fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            return -1;
        }
    }
    else
    {
        fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
        {
            return -1;
        }
    }
    return fd;
}
int check_inpred(char *str)
{
    char *ptr = (char *)malloc(1000 * sizeof(char));
    ptr = strstr(str, "<");
    int fl = 1;
    if (ptr == NULL)
    {
        fl = 0;
    }
    return fl;
}
int check_outred(char *str)
{
    char *ptr = (char *)malloc(1000 * sizeof(char));
    ptr = strstr(str, ">");
    int fl = 0;
    if (ptr != NULL)
    {
        if (strstr(str, ">>") != NULL)
        {
            fl = 2; // 2 for append
        }
        else
        {
            fl = 1;
        }
    }
    return fl;
}
void redirection(char *command)
{
    int org_stdout = dup(1);
    int org_stdin = dup(0);
    int status, in, out;
    char *pt = (char *)malloc(1000 * sizeof(char));
    in = check_inpred(command);
    out = check_outred(command);
    char *copy_command = (char *)malloc(1000 * sizeof(char));
    char *copy_command2 = (char *)malloc(1000 * sizeof(char));
    char *copy_command3 = (char *)malloc(1000 * sizeof(char));
    char *outputf = (char *)malloc(1000 * sizeof(char));
    char *inputf = (char *)malloc(1000 * sizeof(char));
    char *fin_outf = (char *)malloc(1000 * sizeof(char));
    char *fin_inf = (char *)malloc(1000 * sizeof(char));
    char *com = (char *)malloc(1000 * sizeof(char));
    strcpy(copy_command, command);
    strcpy(copy_command2, command);
    strcpy(copy_command3, copy_command2);
    pt = strtok(copy_command2, "><");
    strcpy(com, pt);
    if (in == 1)
    {
        pt = strtok(copy_command3, "<");
        pt = strtok(NULL, ">");
        strcpy(inputf, pt);
        fin_inf = strtok(inputf, " \t");
        if (fin_inf == NULL)
        {
            printf("\x1B[1;31mPlease specify the name of the file for input\n\x1B[1;0m");
            prestat = 'f';
            return;
        }
        else if (check_file(fin_inf) == 0)
        {
            printf("\x1B[1;31mInput file does not exist\n\x1B[1;0m");
            prestat = 'f';
            return;
        }
    }
    char *send = (char *)malloc(1000 * sizeof(char));
    strcpy(send, com);
    if (out == 1 || out == 2)
    {
        pt = strtok(command, ">");
        pt = strtok(NULL, "<");
        strcpy(outputf, pt);
        fin_outf = strtok(outputf, " \t");
        if (fin_outf == NULL)
        {
            printf("\x1B[1;31mEnter output file\n\x1B[1;0m");
            prestat = 'f';
            return;
        }
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("\x1B[1;31mError \x1B[1;0m");
        prestat = 'f';
        return;
    }
    else if (pid == 0)
    {
        if (in == 1)
        {
            int fdin = open(fin_inf, O_RDONLY);
            if (fdin == -1)
            {
                printf("\x1B[1;31mError reading the input file\n\x1B[1;0m");
                prestat = 'f';
                return;
            }
            else if (fdin >= 0)
            {
                dup2(fdin, 0);
                close(fdin);
            }
        }
        if (out == 1 || out == 2)
        {
            int fdout;
            fdout = create_if_not(fin_outf, out);
            if (fdout == -1)
            {
                printf("\x1B[1;31mError writing to the output file\n\x1B[1;0m");
                prestat = 'f';
                return;
            }
            else if (fdout >= 0)
            {
                dup2(fdout, 1);
                close(fdout);
            }
        }
        int y = 0;
        strcpy(colonsep[y], send);
        call_command(1, 1);
        dup2(org_stdin, 0);
        close(org_stdin);
        dup2(org_stdout, 1);
        close(org_stdout);
        exit(0);
    }
    else if (pid >= 1)
    {
        waitpid(pid, &status, 0);
    }
}
