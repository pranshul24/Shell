#include "headers.h"
#include "ls.h"
ll sz4 = 10000;
char *convert(char *tempo)
{
    char *to_convert = (char *)malloc(sz4 * sizeof(char));
    if (tempo[0] == '~')
    {
        strcpy(to_convert, home);
        ll k = strlen(tempo), len = strlen(to_convert), i;
        for (i = 1; i < k; i++)
        {
            to_convert[len + i - 1] = tempo[i];
        }
        to_convert[len + i - 1] = '\0';
        strcpy(tempo, to_convert);
    }
    return tempo;
}
void print_fileorsubdir(char *perm, char *data)
{
    if (perm[0] == 'd')
    {
        printf("\x1B[1;34m%s\x1B[0m\n", data);
    }
    else if (perm[3] == 'x')
    {
        printf("\x1B[1;36m%s\x1B[0m\n", data);
    }
    else
    {
        printf("%s\n", data);
    }
}

void print_permission(char *perm)
{
    printf("%s\t", perm);
}
void print_listed_ls(char *filenameorsubdir, char *filepath)
{

    struct stat f_or_sd;
    long long y = stat(filepath, &f_or_sd);
    if (y == -1)
        perror("Error ");
    else if (y == 0)
    {
        char *time = (char *)malloc(sizeof(char) * 155);
        mode_t p = f_or_sd.st_mode;
        strftime(time, 150, "%b  %d %H:%M", localtime(&f_or_sd.st_mtime));
        char *permission_arr = malloc(sizeof(char) * 15);
        for (ll i = 0; i < 10; i++)
        {
            permission_arr[i] = '-';
        }
        if (stat(filepath, &f_or_sd) == 0 && S_ISDIR(f_or_sd.st_mode))
        {
            permission_arr[0] = 'd';
        }
        if (p & S_IRUSR)
        {
            permission_arr[1] = 'r';
        }
        if (p & S_IWUSR)
        {
            permission_arr[2] = 'w';
        }
        if (p & S_IXUSR)
        {
            permission_arr[3] = 'x';
        }
        if (p & S_IRGRP)
        {
            permission_arr[4] = 'r';
        }
        if (p & S_IWGRP)
        {
            permission_arr[5] = 'w';
        }
        if (p & S_IXGRP)
        {
            permission_arr[6] = 'x';
        }
        if (p & S_IROTH)
        {
            permission_arr[7] = 'r';
        }
        if (p & S_IWOTH)
        {
            permission_arr[8] = 'w';
        }
        if (p & S_IXOTH)
        {
            permission_arr[9] = 'x';
        }
        permission_arr[10] = '\0';
        print_permission(permission_arr);
        struct passwd *owner_struct = getpwuid(f_or_sd.st_uid);
        struct group *group_struct = getgrgid(f_or_sd.st_gid);
        printf("%ld\t%s\t%s\t%ld\t\t %s\t", f_or_sd.st_nlink, owner_struct->pw_name, group_struct->gr_name, f_or_sd.st_size, time);
        print_fileorsubdir(permission_arr, filenameorsubdir);
    }
}
void list_with_l(char *temdir2, ll hidden)
{

    char *filenameorsubdir = (char *)malloc(sz4 * sizeof(char));
    char *filenameorsubdir_appended_on_dir = (char *)malloc(sz4 * sizeof(char));
    DIR *directory;
    directory = opendir(temdir2);

    if (directory == NULL)
    {
        printf("\x1B[1;31mError: Unable to read directory or directory does not exist\n\x1B[0m");
        return;
    }
    struct dirent *file_or_subdir;
    while (file_or_subdir = readdir(directory))
    {
        if (file_or_subdir == NULL)
        {
            break;
        }
        else
        {
            strcpy(filenameorsubdir, file_or_subdir->d_name);
            strcpy(filenameorsubdir_appended_on_dir, temdir2);
            strcat(filenameorsubdir_appended_on_dir, "/");
            strcat(filenameorsubdir_appended_on_dir, filenameorsubdir);
            if (filenameorsubdir[0] != '.' || hidden == 1)
            {
                print_listed_ls(filenameorsubdir, filenameorsubdir_appended_on_dir);
            }
        }
    }
}
void list(char *temdir, ll hidden, ll detail)
{

    if (detail == 1)
    {
        list_with_l(temdir, hidden);
        return;
    }
    DIR *directory;
    directory = opendir(temdir);
    if (directory == NULL)
    {
        printf("\x1B[1;31mError: Unable to read directory or directory does not exist\n\x1B[0m");
        return;
    }
    struct dirent *file_or_subdir;
    char *filename = (char *)malloc(sz4 * sizeof(char));
    while (file_or_subdir = readdir(directory))
    {
        if (file_or_subdir == NULL)
        {
            break;
        }
        else
        {
            strcpy(filename, file_or_subdir->d_name);
            if (filename[0] != '.' || hidden == 1)
                printf("%s\n", filename);
        }
    }
    closedir(directory);
}
void ls(char *argument)
{

    ll k = 0;
    ll i, j;
    char del[] = " \t";
    char *ptr;
    if (argument != NULL)
        ptr = strtok(argument, del);
    char flag_arr[50][100], dir_arr[25][100];
    ll fk = 0, dk = 0;
    ll hidden = 0, detail = 0;
    if (argument != NULL)
    {
        while (ptr != NULL)
        {
            if (ptr[0] == '-')
            {
                strcpy(flag_arr[fk], ptr);
                fk++;
            }
            else
            {
                strcpy(dir_arr[dk], ptr);
                dk++;
            }
            ptr = strtok(NULL, del);
        }
        for (i = 0; i < fk; i++)
        {
            for (j = 1; j < strlen(flag_arr[i]); j++)
            {
                if (flag_arr[i][j] == 'l')
                    detail = 1;
                if (flag_arr[i][j] == 'a')
                    hidden = 1;
                if (detail == 1 && hidden == 1)
                    break;
            }
            if (detail == 1 && hidden == 1)
                break;
        }
    }
    if (dk == 0)
    {
        char *cwdir = (char *)malloc(1000 * sizeof(char));
        getcwd(cwdir, 1000 - 5);
        strcpy(dir_arr[0], cwdir);
        dk = 1;
    }
    for (i = 0; i < dk; i++)
    {
        if (dk > 1)
        {
            printf("%s:\n", dir_arr[i]);
        }
        strcpy(dir_arr[i], convert(dir_arr[i]));
        list(dir_arr[i], hidden, detail);
        if (i < dk - 1)
            printf("\n");
    }
}