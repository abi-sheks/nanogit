#include <iostream>
#include <string>
#include "./src/lib.cpp"

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cout << "ERROR : Arguments invalid" << '\n';
    }
    else
    {
        auto arg_as_string = std::string(argv[1]);
        if (arg_as_string == "init")
        {
            std::cout << "Happening?";
            init();
        }
        else if (arg_as_string == "add")
        {
            std::cout << "Happening?";
            add(std::string(argv[2]));
        }
        else if (arg_as_string == "rm")
        {
            std::cout << "Happening?";
            rm(std::string(argv[2]));
        }
        else if (arg_as_string == "commit")
        {
            std::cout << "Happening?";
            commit(std::string(argv[2]));
        }
    }
    return 0;
}