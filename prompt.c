#include "prompt.h"
#include "headers.h"
#define ll long long
struct utsname sysname;
size_t sz1 = 1e3, sz2 = 1e3 + 4;
ll i;
void modify(char *cwdir)
{
    ll l = strlen(home), k = strlen(cwdir);
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
void prompt_stdout(char *home)
{
    char *systemname = (char *)malloc(sz2 * sizeof(char));
    ll system_name = uname(&sysname);
    systemname = sysname.nodename;
    char *username = (char *)malloc(sz2 * sizeof(char));
    ll user = getlogin_r(username, sz2 - 5);
    char *cwdir = (char *)malloc(sz1 * sizeof(char));
    getcwd(cwdir, sz1 - 5);
    if (system_name == -1)
    {
        //Error
        printf("\x1B[1;31mError getting the host name\n\x1B[0m");
        return;
    }
    else
    {
        if (user != 0)
        {
            //Error
            printf("\x1B[1;31mError getting the username\n\x1B[0m");
            return;
        }
        else
        {
            if (cwdir == NULL)
            {
                //Error
                printf("\x1B[1;31mError getting the current working directory\n\x1B[0m");
                return;
            }
            else
            {
                modify(cwdir);
                if (prestat == 'n')
                {
                    printf("\x1B[1;34m<\x1B[1;33m%s\x1B[1;34m@\x1B[1;33m%s:\x1B[0;32m%s\x1B[1;34m>\x1B[0m", username, systemname, cwdir);
                }
                else if (prestat == 'f')
                {
                    printf("\x1B[1;31m:'(\x1B[1;34m<\x1B[1;33m%s\x1B[1;34m@\x1B[1;33m%s:\x1B[0;32m%s\x1B[1;34m>\x1B[0m", username, systemname, cwdir);
                }
                else if (prestat == 's')
                {
                    printf("\x1B[1;32m:')\x1B[1;34m<\x1B[1;33m%s\x1B[1;34m@\x1B[1;33m%s:\x1B[0;32m%s\x1B[1;34m>\x1B[0m", username, systemname, cwdir);
                }
            }
        }
    }
}