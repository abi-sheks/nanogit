#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "util.h"

void init()
{
    fs_mkdir(".nanogit");
    FILE *index = fopen(".nanogit/.index", "w");
    FILE *prev = fopen(".nanogit/.prev", "w");
    if (!index || !prev)
    {
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 40; i++)
    {
        putc('0', prev);
    }
    fclose(index);
    fclose(prev);
}

void add(const char *filename)
{
    FILE *index = fopen(".nanogit/.index", "r");
    if (!is_file(filename))
    {
        exit(EXIT_FAILURE);
    }
    bool already_added = false;
    ssize_t read;
    size_t len = 0;
    char *line = NULL;
    strcat(filename, "\n");
    while ((read = getline(&line, &len, index)) != -1)
    {
        if (strcmp(filename, line) == 0)
        {
            already_added = true;
        }
    }
    if (already_added)
    {
        exit(EXIT_FAILURE);
    }
    fclose(index);
    strtok(filename, "\n");
    FILE *edit = fopen(".nanogit/.index", "a");
    fprintf(edit, filename);
    fprintf(edit, "\n");
    fclose(edit);
}

void rm(const char *filename)
{
    FILE *index = fopen(".nanogit/.index", "r");
    FILE *replica = fopen(".nanogit/.new_index", "w");
    if (!index || !replica)
    {
        exit(EXIT_FAILURE);
    }
    ssize_t read;
    size_t len = 0;
    char *line = NULL;
    while ((read = getline(&line, &len, index)) != -1)
    {
        strtok(line, "\n");
        if (strcmp(line, filename) != 0)
        {
            fprintf(replica, line);
            fprintf(replica, "\n");
        }
    }
    fclose(index);
    fclose(replica);
    fs_rm(".nanogit/.index");
    rename(".nanogit/.new_index", ".nanogit/.index");
}