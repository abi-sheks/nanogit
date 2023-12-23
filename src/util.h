#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

struct stat st = {0};

void fs_mkdir(const char* dir)
{
    if(stat(dir, &st) == -1)
    {
        mkdir(dir, 0700);
    }
}

void fs_rm(const char*filename)
{
    
}