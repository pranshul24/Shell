#include "headers.h"
#include "handle_env.h"
void set_env_var(char *argu)
{
    char *pt = (char *)malloc(1005 * sizeof(char));
    char *variable = (char *)malloc(1000 * sizeof(char));
    char *variable_value = (char *)malloc(1000 * sizeof(char));
    strcpy(variable_value, "");
    pt = strtok(argu, " \t");
    if (pt == NULL)
    {
        printf("\x1B[1;31mError : enter arguments !!!\x1B[0m\n");
        return;
    }
    else if (pt != NULL)
    {
        strcpy(variable, pt);
        pt = strtok(NULL, " \t");
        if (pt == NULL)
        {
            int k = setenv(variable, variable_value, 1); //1 == allow overwrite
            if (k == -1)
            {
                perror("\x1B[1;31mError \x1B[0m");
                return;
            }
        }
        else if (pt != NULL)
        {
            strcpy(variable_value, pt);
            pt = strtok(NULL, " \t");
            if (pt == NULL)
            {
                int k = setenv(variable, variable_value, 1);
                if (k == -1)
                {
                    perror("\x1B[1;31mError \x1B[0m");
                    return;
                }
            }
            else if (pt != NULL)
            {
                printf("\x1B[1;31mError : enter less than 3 arguments !!!\x1B[0m\n");
                return;
            }
        }
    }
}
void unset_env_var(char *argu)
{
    char *pt = (char *)malloc(1005 * sizeof(char));
    char *variable = (char *)malloc(1000 * sizeof(char));
    pt = strtok(argu, " \t");
    if (pt == NULL)
    {
        printf("\x1B[1;31mError : enter the environment variable name !!!\x1B[0m\n");
        return;
    }
    else if (pt != NULL)
    {
        strcpy(variable, pt);
        pt = strtok(NULL, " \t");
        if (pt == NULL)
        {
            int k = unsetenv(variable); //1 == allow overwrite
            if (k == -1)
            {
                perror("\x1B[1;31mError \x1B[0m");
                return;
            }
        }
        else if (pt != NULL)
        {
            printf("\x1B[1;31mError : enter less than 2 arguments !!!\x1B[0m\n");
            return;
        }
    }
}