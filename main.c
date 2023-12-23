#include <stdio.h>
#include <string.h>
#include "./src/lib.c"

int main(int argc, char**argv)
{
    if(argc < 2)
    {
        fprintf(stdout, "ERROR : Arguments invalid\n");
    }
    else
    {
        if(strcmp(argv[1], "init") == 0)
        {
            init();
        }
        else if(strcmp(argv[1], "add") == 0)
        {
            add(argv[2]);
        }
        else if(strcmp(argv[1], "rm") == 0)
        {
            rm(argv[2]);
        }
    }
    return 0;
}