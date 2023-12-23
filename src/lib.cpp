#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include "util.h"
#include "commit.h"

void init()
{
    fs_mkdir(".nanogit");
    std::ofstream index(".nanogit/.index");
    std::ofstream prev(".nanogit/.prev");
    if (!index || !prev)
    {
        throw std::runtime_error("Files could not be made");
    }
    std::string init_commit = std::string(40, '0');
    prev << init_commit;
    index.close();
    prev.close();
}

void add(const std::string filename)
{
    std::vector<std::string> tracked_files;
    std::ifstream index(".nanogit/.index");
    if (!is_exists(filename))
    {
        throw std::runtime_error("Not a file");
    }
    bool already_added = false;
    std::string line;
    while (std::getline(index, line))
    {
        if (filename == line)
        {
            already_added = true;
        }
    }
    if (already_added)
    {
        throw std::runtime_error("Already added");
    }
    index.close();
    std::ofstream edit;
    edit.open(".nanogit/.index", std::ios::app);
    edit << filename << "\n";
    edit.close();
}

void rm(const std::string filename)
{
    std::ifstream index(".nanogit/.index");
    std::ofstream replica(".nanogit/.new_index");
    if (!index || !replica)
    {
        throw std::runtime_error("Failed to open");
    }
    std::string line;
    while (std::getline(index, line))
    {
        if (filename != line)
        {
            replica << line << "\n";
        }
    }
    index.close();
    replica.close();
    fs_rm(".nanogit/.index");
    fs::rename(".nanogit/.new_index", ".nanogit/.index");
}

void commit(const std::string message)
{
    auto current_path = fs::current_path();
    std::string commit_id = generate_commit_id();
    // set up new directory and .prev and .msg
    auto previous_commit = read_string_from_file(".nanogit/.prev");
    auto new_dir = ".nanogit/" + commit_id;
    fs::create_directory(new_dir);
    write_string_to_file(new_dir + "/.msg", message);
    write_string_to_file(new_dir + "/.prev", previous_commit);
    // transfer state
    std::ifstream index(".nanogit/.index");
    std::string line;
    while (std::getline(index, line))
    {
        if (is_exists(std::string(current_path) + "/" + line))
        {
            fs::copy(fs::path(std::string(current_path) + "/" + line), fs::path(std::string(current_path) + "/" + new_dir + "/" + line));
        }
    }
    // replace global prev with current commit
    write_string_to_file(".nanogit/.prev", commit_id);
}