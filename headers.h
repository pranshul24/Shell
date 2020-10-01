#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/times.h>
#include <pwd.h>
#include <grp.h>
#include <signal.h>
#include <wait.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <termios.h>
#include <sys/ioctl.h>
#define ll long long
char home[10005];
long long no, back_g, hist_cnt;
char hist_filename[1000];
char hist[22][500];
int total_back_process;
char process_name[35000][50];
char dirprev[2005], dirnow[2005];
int pid_arr[35000];
int fg_pid;
int spid;
char colonsep[100][1000];
char pipe_args[100][1000];
char or_args[10][100];
char and_args[10][100];
char prestat;