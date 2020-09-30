#include "headers.h"
#include "pwd.h"
void pwd(char *tempor)
{

    long long sz = 10004, k = 0, i;
    if (tempor != NULL)
    {
        k = strlen(tempor);
    }
    for (i = 0; i < k; i++)
    {
        if (tempor[i] != ' ')
            break;
    }
    char *pt = (char *)malloc(sizeof(char) * 100);
    pt = strtok(tempor + i, " \t");
    if (pt != NULL)
    {
        printf("\x1B[1;31mCan't pass arguments to pwd!!!\x1B[0m\n");
        prestat = 'f';
        return;
    }
    char *curworkdir = (char *)malloc(sizeof(char) * sz);
    getcwd(curworkdir, sz - 5);
    if (curworkdir == NULL)
    {
        //Error
        printf("\x1B[1;31mError getting the current working directory\n\x1B[0m");
        prestat = 'f';
        return;
    }
    else
    {
        printf("%s\n", curworkdir);
    }
}
