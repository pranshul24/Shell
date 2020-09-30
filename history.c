#include "headers.h"
#include "history.h"

long long hist_i;
void rewrite_his()
{
    FILE *fptr;
    fptr = fopen(hist_filename, "w");
    if (fptr != NULL)
    {
        for (long long i = 0; i < hist_cnt; i++)
        {
            if (i != hist_cnt - 1)
            {
                fprintf(fptr, "%s", hist[i]);
                fprintf(fptr, "\n");
            }
            else
            {
                fprintf(fptr, "%s", hist[i]);
            }
        }
    }
    fclose(fptr);
}
void disp_his(long long n)
{
    long long start;
    if (hist_cnt < n)
    {
        start = 0;
    }
    else
    {
        start = hist_cnt - n;
    }
    for (long long i = start; i < hist_cnt; i++)
    {
        printf("%s\n", hist[i]);
    }
}
long long get_count_his()
{
    FILE *fptr2;
    fptr2 = fopen(hist_filename, "r");
    char *single_line = (char *)malloc(sizeof(char) * 450);
    long long i = 0;
    while (fgets(single_line, 445, fptr2))
    {
        strcpy(hist[i], single_line);
        if (hist[i][strlen(hist[i]) - 1] == '\n')
        {
            hist[i][strlen(hist[i]) - 1] = '\0';
        }
        i++;
    }
    fclose(fptr2);
    return i;
}
void write_his(char *add_on)
{
    if (hist_cnt > 0)
    {
        if (strcmp(hist[hist_cnt - 1], add_on) == 0)
            return;
    }
    FILE *fptr;
    fptr = fopen(hist_filename, "w");
    if (fptr == NULL)
    {
        printf("Error opening the history_store.txt file ! Could not write the last instruction\n");
        prestat = 'f';
        return;
    }
    if (hist_cnt < 20)
    {
        strcpy(hist[hist_cnt], add_on);
        ++hist_cnt;
    }
    else
    {
        for (long long i = 0; i < 19; i++)
        {
            strcpy(hist[i], hist[i + 1]);
        }
        strcpy(hist[19], add_on);
    }

    for (long long i = 0; i < hist_cnt; i++)
    {
        if (i != hist_cnt - 1)
        {
            fprintf(fptr, "%s", hist[i]);
            fprintf(fptr, "\n");
        }
        else
        {
            fprintf(fptr, "%s", hist[i]);
        }
    }
    fclose(fptr);
}

void history(char *argu)
{
    char *token;
    token = strtok(argu, " \t");
    if (token == NULL)
    {
        disp_his(10);
        return;
    }
    char *arg_fst = (char *)malloc(sizeof(char) * 100);
    strcpy(arg_fst, token);
    token = strtok(NULL, " \t");
    if (token != NULL)
    {
        printf("Sorry you can add at max 1 argument !!!");
        prestat = 'f';
    }
    else
    {
        disp_his(atoi(arg_fst));
    }
}