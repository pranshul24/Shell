#include "headers.h"
#include "manage_signal.h"
#include "run.h"
#include "prompt.h"
char stat_string[200];
void exit_fg(int signum)
{
    pid_t p = getpid();
    if (p != spid)
    {
        return;
    }
    else if (fg_pid != -1)
    {
        kill(fg_pid, SIGINT);
    }
    signal(SIGINT, exit_fg);
    return;
}
void to_bg(int signum)
{
    pid_t p = getpid();
    if (p != spid)
    {
        return;
    }
    else if (fg_pid != -1)
    {
        kill(fg_pid, SIGTSTP);
        //raise(SIGTSTP);
    }
    return;
}
void end(int sig_num)
{
    int loc;
    pid_t pid = waitpid(-1, &loc, WNOHANG);
    if (pid < 1)
    {
        return;
    }
    else if (pid >= 1)
    {
        if (WIFEXITED(loc) && WEXITSTATUS(loc) == 0)
        {
            sprintf(stat_string, "\x1B[1;32m\n%s with pid %d exited normally !!!\n\x1B[0m", process_name[pid], pid);
            print_status(stat_string);
        }
        else
        {
            sprintf(stat_string, "\x1B[1;31m\n%s with pid %d exited abnormally !!!\n\x1B[0m", process_name[pid], pid);
            prestat = 'f';
            print_status(stat_string);
        }
        manage_pid_arr(pid);
        total_back_process--;
    }
    prompt_stdout(home);
    fflush(stdout);
    return;
}