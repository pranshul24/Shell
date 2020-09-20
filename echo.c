#include "headers.h"
#include "echo.h"
void echo(char *argument)
{
    char *string2 = argument;
    long long h = strlen(string2), i;
    for (i = 0; i < h; i++)
    {
        if (string2[i] != ' ')
            break;
    }
    char arr_string2[1000][100], *ptr;
    ptr = strtok(string2 + i, " \t");
    long long len = 0;
    while (ptr != NULL)
    {
        strcpy(arr_string2[len], ptr);
        len++;
        ptr = strtok(NULL, " \t");
    }
    for (i = 0; i < len; i++)
    {
        printf("%s ", arr_string2[i]);
    }
    printf("\n");
}