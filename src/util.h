#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>

void fs_mkdir(const char *dir)
{
    struct stat st = {0};
    if (stat(dir, &st) == -1)
    {
        mkdir(dir, 0700);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
}

void fs_rm(const char *filename)
{
    if (remove(filename) != 0)
    {
        exit(EXIT_FAILURE);
    }
}

bool is_file(const char *filename)
{
    struct stat buffer;
    struct stat b2;
    stat(filename, &b2);
    //checks whether file exists and is a file
    return (stat(filename, &buffer) == 0) && S_ISREG(b2.st_mode);
}