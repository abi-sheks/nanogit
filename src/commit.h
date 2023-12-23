#pragma once
#include <ctime>
#include <string>
#include <iostream>
#include <cstdlib>

std::string generate_commit_id()
{
    // for now, commitids are made up entirely of '5', '0', and 'b'
    std::string commit_id = "";
    srand(time(0));
    for (int i = 0; i < 40; i++)
    {
        int random_no = rand() % 3;
        if (random_no == 0)
            commit_id += "5";
        else if (random_no == 1)
            commit_id += "0";
        else
            commit_id += "b";
    }
    return commit_id;
}