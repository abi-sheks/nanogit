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
            init();
        }
        else if (arg_as_string == "add")
        {
            add(std::string(argv[2]));
        }
        else if (arg_as_string == "rm")
        {
            rm(std::string(argv[2]));
        }
        else if (arg_as_string == "commit")
        {
            if (argc != 4)
            {
                throw std::invalid_argument("ERROR : Number of arguments incorrect");
            }
            if (std::string(argv[2]) != "-m")
            {
                throw std::invalid_argument("ERROR : use -m to specify message");
            }
            commit(std::string(argv[3]));
        }
    }
    return 0;
}