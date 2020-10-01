#include "headers.h"
#include "main.h"
#include "logical_chain.h"
int numb_of_op(char *input)
{
    int i, n = strlen(input), no = 0;
    for (i = 0; i < n; i++)
    {
        if (input[i] == '@' || input[i] == '$')
        {
            args_operators[no] = input[i];
            no++;
        }
    }
    return no;
}
int numb_and_or(char *input)
{
    char *p = strtok(input, "@$");
    no = 0;
    while (p != NULL)
    {
        strcpy(and_or_args[no], p);
        no++;
        p = strtok(NULL, "@$");
    }
    return no;
}
void chain(char *str)
{
    int totn = numb_of_op(str);
    int tota = numb_and_or(str);
    if (tota - 1 != totn)
    {
        printf("\x1B[1;31mParse Error in chaining !\x1B[0m\n");
        prestat = 'f';
        return;
    }
    int i;

    for (i = 0; i < tota; i++)
    {
        strcpy(colonsep[0], and_or_args[i]);
        call_command(1, 0);
        if (i < tota - 1)
        {
            if (prestat == 's')
            {
                if (args_operators[i] == '@')
                {
                    continue;
                }
                else if (args_operators[i] == '$')
                {
                    while (args_operators[i] == '$')
                    {
                        i++;
                    }
                    continue;
                }
            }
            else if (prestat == 'f')
            {
                if (args_operators[i] == '@')
                {
                    while (args_operators[i] == '@')
                    {
                        i++;
                    }
                    continue;
                }
                else if (args_operators[i] == '$')
                {
                    continue;
                }
            }
        }
    }
}