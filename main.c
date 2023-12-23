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
            fprintf(stdout, "add logic here\n");
        }
    }
    return 0;
}