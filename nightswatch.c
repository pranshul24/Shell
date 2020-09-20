#include "headers.h"
#include "nightswatch.h"
char *if_interrupt(char *file)
{
    char *send_if_fail = (char *)malloc(sizeof(char) * 400);
    FILE *fptr3 = fopen(file, "r");
    sprintf(send_if_fail, "Sorry can't open the required file -> %s\n", file);
    if (fptr3 == NULL)
    {
        return send_if_fail;
    }
    else if (fptr3 != NULL)
    {
        long long i = 0;
        char *single_line = (char *)malloc(sizeof(char) * 400);
        while (fgets(single_line, 390, fptr3))
        {
            i++;
            if (i == 3)
                break;
        }
        char *pt = strtok(single_line, ":");
        pt = strtok(NULL, "");
        strcpy(single_line, pt);
        long long k = strlen(single_line);
        i = 0;
        while (i < k)
        {
            if (single_line[i] == 'I')
            {
                break;
            }
            else
            {
                i++;
            }
        }
        single_line[i] = '\0';
        fclose(fptr3);
        return single_line;
    }
}
void nwatch(char *str)
{
    char pos[] = "/proc/interrupts", a[] = "    ";
    char *arr_string5[10];
    long long i;
    char *ptr = (char *)malloc(sizeof(char) * 100);
    ptr = strtok(str, " \t");
    long long len = 0;
    while (ptr != NULL)
    {
        arr_string5[len] = ptr;
        len++;
        ptr = strtok(NULL, " \t");
    }
    arr_string5[len] = NULL;
    long long after_sec;
    if (len == 1)
    {
        if (strcmp("interrupt", arr_string5[0]) == 0)
        {
            after_sec = 5; //default value
        }
        else
        {
            printf("\x1B[1;31mPlease enter the valid arguments for nightswatch!!!\x1B[0m\n");
            return;
        }
    }
    else if (len == 3)
    {
        long long f = 0;
        after_sec = atoi(arr_string5[1]);
        if (after_sec == 0)
        {
            printf("\x1B[1;31mInappropriate seconds specified !!! Should be a natural number \x1B[0m\n");
            f = 1;
        }
        if (strcmp("-n", arr_string5[0]) != 0)
        {
            printf("\x1B[1;31m%s is not a valid option !!! \x1B[0m\n", arr_string5[0]);
            f = 1;
        }
        if (strcmp("interrupt", arr_string5[2]) != 0)
        {
            printf("\x1B[1;31m%s is not a valid argument for nightswatch!!! Do you mean <interrupt> ? \x1B[0m\n", arr_string5[2]);
            f = 1;
        }
        if (f == 1)
        {
            return;
        }
    }
    else
    {
        printf("\x1B[1;31mPlease mention the arguments !!!\n\x1B[0m");
        return;
    }
    FILE *interrupt_file = fopen(pos, "r");
    char *single_line = (char *)malloc(sizeof(char) * 400);
    if (interrupt_file == NULL)
    {
        printf("\x1B[1;31mSorry can't open the file needed to read interrupt count!!!\n\x1B[0m");
        return;
    }
    else if (interrupt_file != NULL)
    {
        fgets(single_line, 390, interrupt_file);
        printf("%s\x1B[1;36m%s\n\x1B[0m", a, single_line);
        fclose(interrupt_file);
    }
    long long k = 1;
    while (k == 1)
    {
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(0, &read_fds);
        char *str = (char *)malloc(sizeof(char) * 200);
        struct timeval tmx;
        tmx.tv_sec = 0;
        tmx.tv_usec = 0;
        long long output_select;
        output_select = select(1, &read_fds, NULL, NULL, &tmx); //nfds,readfds,writefds,exceptfds,timeout
        if (output_select == -1)
        {
            perror("Error ");
        }
        else if (output_select > 0)
        {
            fgets(str, 175, stdin);
            str[strlen(str) - 1] = '\0';
            if (strlen(str) == 1)
            {
                if (str[0] == 'q')
                    return;
            }
        }
        printf("\t%s\n", if_interrupt(pos));
        sleep(after_sec);
    }
}
//nightswatch -n 2 interrupt