#include "headers.h"
#include "changedir.h"
#include "pinfo.h"
ll sz3 = 1e4;
void cd(char *argument)
{
    int fl = 0;
    char *to_change_dir = (char *)malloc(sz3 * sizeof(char));
    char *var = (char *)malloc(sz3 * sizeof(char));
    ll k, i;
    var = strtok(argument, " \t");
    char *to_change_dir_absolute = (char *)malloc(sz3 * sizeof(char));
    k = 0;
    if (var != NULL)
    {
        strcpy(to_change_dir, var);
        k = strlen(to_change_dir);
        var = strtok(NULL, " \t");
        if (var != NULL)
        {
            printf("\x1B[1;31mEnter 1 argument at max!!!\n\x1B[0m");
            return;
        }
        else
        {
            if (strcmp(to_change_dir, "-") == 0)
            {
                strcpy(to_change_dir, dirprev);
                fl = 1;
            }
        }
    }
    else
    {
        to_change_dir[0] = '~';
        to_change_dir[1] = '\0';
    }

    if (to_change_dir != NULL && to_change_dir[0] == '~')
    {
        strcpy(to_change_dir_absolute, home);
        ll var = strlen(to_change_dir_absolute);
        i = 1;
        while (i < k)
        {
            to_change_dir_absolute[var + i - 1] = to_change_dir[i];
            i++;
        }
        strcpy(to_change_dir, to_change_dir_absolute);
    }
    if (to_change_dir == NULL)
    {
        strcpy(to_change_dir, home);
    }
    ll flag = 0;
    flag = chdir(to_change_dir); // 0 if success
    if (flag == -1)
    {
        perror("\x1B[1;31mError \x1B[0m");
    }
    else
    {
        strcpy(dirprev, dirnow);
        char *cwdir = (char *)malloc(1000 * sizeof(char));
        getcwd(cwdir, 1000 - 5);
        if (cwdir != NULL)
        {
            strcpy(dirnow, cwdir);
        }
        if (fl == 1)
        {
            if (cwdir == NULL)
            {
                printf("\x1B[1;31mError getting the directory path\n\x1B[0m");
                return;
            }
            else
            {
                modify2(cwdir);
                printf("%s\n", cwdir);
            }
        }
    }
}