#include "headers.h"
#include "pinfo.h"
void modify2(char *cwdir)
{
    ll i, sz1 = 1000, l = strlen(home), k = strlen(cwdir);
    char *temstr = (char *)malloc(sz1 * sizeof(char));
    temstr[0] = '~';
    ll flag = 0;
    if (k >= l)
    {
        for (i = 0; i < l; i++)
        {
            if (cwdir[i] != home[i])
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            if (cwdir[l] != '/' && cwdir[l] != '\0')
            {
                flag = 1;
            }
            if (flag == 0)
            {
                i = l;
                while (i < k)
                {
                    temstr[i + 1 - l] = cwdir[i];
                    i++;
                }
                temstr[k - l + 1] = '\0';
                strcpy(cwdir, temstr);
            }
        }
    }
}
void pinfo(char *process_id)
{
    long long i;
    char *ptr = (char *)malloc(sizeof(char) * 2000);
    ptr = strtok(process_id, " \t");
    char fst[2005];
    if (ptr != NULL)
    {
        strcpy(fst, ptr);
    }
    pid_t pid;
    long long k = 0;
    while (ptr != NULL)
    {
        k++;
        ptr = strtok(NULL, " \t");
    }
    if (k == 0)
    {
        pid = getpid();
    }
    else if (k > 1)
    {
        printf("\x1B[1;31mToo many arguments(pids)! Enter no more than 1 pid at a time !\x1B[0m\n");
        return;
    }
    else if (k == 1)
    {
        pid = atoi(fst);
    }
    char *exe_file = malloc(sizeof(char) * (1000));
    char *status_file = malloc(sizeof(char) * (1000));
    char *buf = malloc(sizeof(char) * (1000));
    strcpy(exe_file, "/proc/");
    strcpy(status_file, "/proc/");
    sprintf(buf, "%d", pid);
    strcat(exe_file, buf);
    strcat(status_file, buf);
    strcat(exe_file, "/exe");
    strcat(status_file, "/status");
    FILE *fileptr = fopen(status_file, "r");

    if (fileptr == NULL)
    {
        if (pid == 0)
        {
            printf("\x1B[1;31mNot a valid pid !!!\x1B[0m\n");
        }
        else
            printf("\x1B[1;31mProcess with pid \x1B[1;34m%d\x1B[1;31m does not exist. Please check the pid!!!\n\x1B[0m", pid);
    }
    else if (fileptr != NULL)
    {
        char *single_line = (char *)malloc(sizeof(char) * 300);
        char *process_status = (char *)malloc(sizeof(char) * 305);
        char *virtual_memory = (char *)malloc(sizeof(char) * 305);
        long long i = 0;
        while (fgets(single_line, 295, fileptr))
        {
            i++;
            if (i == 3)
            {
                strcpy(process_status, single_line);
            }
            else if (i == 18)
            {
                strcpy(virtual_memory, single_line);
            }
        }
        fclose(fileptr);
        char *st1 = strtok(process_status, ":");
        st1 = strtok(NULL, " \t");
        char *exepath = (char *)malloc(sizeof(char) * 1005);
        printf("\x1B[1;35mPid -- \x1B[0;32m%d\n", pid);
        printf("\x1B[1;35mProcess Status -- \x1B[0;32m%s\n", st1);
        char *st2 = strtok(virtual_memory, "\t");
        st2 = strtok(NULL, " \t");
        printf("\x1B[1;35mMemory -- \x1B[0;32m%s\n", st2);
        long long ret = readlink(exe_file, exepath, 1000);
        if (ret == -1)
            printf("\x1B[1;31mExecutable Path Not Found\n");
        else if (ret != -1)
        {
            exepath[ret] = '\0';
            modify2(exepath);
            printf("\x1B[1;35mExecutable path -- \x1B[0;32m%s\n\x1B[0m", exepath);
        }
    }
}