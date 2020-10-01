#include "headers.h"
#include "main.h"
#include "logical_chain.h"
int numb_or(char *input)
{
    char *p = strtok(input, "$");
    no = 0;
    while (p != NULL)
    {
        strcpy(or_args[no], p);
        no++;
        p = strtok(NULL, "$");
    }
    return no;
}
int numb_and(char *input)
{
    char *p = strtok(input, "@");
    no = 0;
    while (p != NULL)
    {
        strcpy(and_args[no], p);
        no++;
        p = strtok(NULL, "@");
    }
    return no;
}
void chain(char *str)
{
    int tota = numb_and(str);
    int flag_and = 0, i;
    for (i = 0; i < tota; i++)
    {
        int toto = numb_or(and_args[i]);
        int j;
        for (j = 0; j < toto; j++)
        {
            strcpy(colonsep[0], or_args[j]);
            call_command(1, 0);
            if (prestat == 's')
            {
                break;
            }
        }
        if (prestat == 'f')
        {
            break;
        }
    }
}