#ifndef __MAIN_H
#define __MAIN_H
int check_for_piping(char *);
int check_for_redirection(char *);
long long sep(char *);
void call_command(int, int);
int check_chain(char *);
void exit_fun();
#endif