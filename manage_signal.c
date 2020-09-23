#include "headers.h"
#include "manage_signal.h"
void exit_fg(int signum)
{
    pid_t p = getpid();
    if (p < 0)
        perror("Error");

    else if (p != spid)
        return;

    if (fg_pid != -1)
        kill(fg_pid, SIGINT);

    signal(SIGINT, exit_fg);
    return;
}