#include "headers.h"
#include "manage_jobs.h"
#include "run.h"
char *status_proc(int pd)
{
    char *status_file = malloc(sizeof(char) * (1000));
    char *buf = malloc(sizeof(char) * (1000));
    strcpy(status_file, "/proc/");
    sprintf(buf, "%d", pd);
    strcat(status_file, buf);
    strcat(status_file, "/status");
    FILE *fileptr = fopen(status_file, "r");
    if (fileptr == NULL)
    {
        return "perror";
    }
    else if (fileptr != NULL)
    {
        char *single_line = (char *)malloc(sizeof(char) * 300);
        char *process_status = (char *)malloc(sizeof(char) * 305);
        long long i = 0;
        while (fgets(single_line, 295, fileptr))
        {
            i++;
            if (i == 3)
            {
                strcpy(process_status, single_line);
                break;
            }
        }
        fclose(fileptr);
        char *st1 = strtok(process_status, ":");
        st1 = strtok(NULL, " \t");
        if (st1[0] == 'T')
            strcpy(process_status, "Stopped");
        else if (st1[0] != 'T')
        {
            strcpy(process_status, "Running");
        }
        return process_status;
    }
}
void print_jobs(char *argu)
{
    char *pt = (char *)malloc(1000 * sizeof(char));
    pt = strtok(argu, " \t");
    if (pt != NULL)
    {
        printf("\x1B[1;31mError : can't enter arguments for jobs command !!!\x1B[0m\n");
        return;
    }
    else if (pt == NULL)
    {
        int i;
        if (total_back_process >= 1)
        {
            for (i = 0; i < total_back_process; i++)
            {
                printf("[%d] %s %s [%d]\n", i + 1, status_proc(pid_arr[i]), process_name[pid_arr[i]], pid_arr[i]);
            }
        }
        else if (total_back_process == 0)
        {
            printf("No background processes\n");
        }
    }
}
void kjob(char *argu)
{
    char *pt = (char *)malloc(1000 * sizeof(char));
    pt = strtok(argu, " \t");
    if (pt == NULL)
    {
        printf("\x1B[1;31mError : enter arguments correctly !!!\x1B[0m\n");
        return;
    }
    else if (pt != NULL)
    {
        char *job_num = (char *)malloc(100 * sizeof(char));
        char *sig_num = (char *)malloc(100 * sizeof(char));
        strcpy(job_num, pt);
        pt = strtok(NULL, " \t");
        if (pt == NULL)
        {
            printf("\x1B[1;31mError : enter arguments correctly !!!\x1B[0m\n");
            return;
        }
        else if (pt != NULL)
        {
            strcpy(sig_num, pt);
            pt = strtok(NULL, " \t");
            if (pt == NULL)
            {
                int jobn = atoi(job_num), sign = atoi(sig_num);
                if (jobn == 0 || jobn > total_back_process)
                {
                    printf("\x1B[1;31mError : enter job number correctly !!!\x1B[0m\n");
                    return;
                }
                else
                {
                    kill(pid_arr[jobn - 1], sign);
                }
            }
            else if (pt != NULL)
            {
                printf("\x1B[1;31mError : specify correct number of arguments for kjob command !!!\x1B[0m\n");
                return;
            }
        }
    }
}