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
    // starting on main
    fs_mkdir(".nanogit");
    write_string_to_file(".nanogit/.branches", "main\n");
    write_string_to_file(".nanogit/.current_branch", "main");
    std::string init_commit = std::string(40, '0');
    write_string_to_file(".nanogit/.branch_main", init_commit);
    std::ofstream index(".nanogit/.index");
    if (!index)
    {
        throw std::runtime_error("Files could not be made");
    }
    index.close();
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
    auto current_branch = read_string_from_file(".nanogit/.current_branch");
    if(current_branch == "DETACHED")
    {
        throw std::runtime_error("ERROR : You can only commit from the HEAD of a branch");
    }
    auto current_path = fs::current_path();
    std::string commit_id = generate_commit_id();
    // set up new directory and .prev and .msg
    auto previous_commit = read_string_from_file(".nanogit/.branch_" + current_branch);
    write_string_to_file(".nanogit/.branch_" + current_branch, commit_id);
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
}

void branch()
{
    auto current_branch = read_string_from_file(".nanogit/.current_branch");
    std::ifstream branches(".nanogit/.branches");
    std::string branch;
    while (std::getline(branches, branch))
    {
        std::cout << branch;
        if (branch == current_branch)
        {
            std::cout << " *";
        }
        std::cout << '\n';
    }
}

// returns branch of which it is head, otherwise returns DETACHED
std::string return_head_branch(const std::string commit_id)
{
    std::ifstream branches(".nanogit/.branches");
    std::string branch;
    while (std::getline(branches, branch))
    {
        auto head_commit = read_string_from_file(".nanogit/.branch_" + branch);
        if (head_commit == commit_id)
        {
            return branch;
        }
    }
    return "DETACHED";
}
void checkout_id(const std::string target)
{
    auto commit_dir = ".nanogit/" + target;
    restore_state(commit_dir);
}
void checkout_branch(const std::string target)
{
    std::ifstream branches(".nanogit/.branches");
    std::string branch;
    while (std::getline(branches, branch))
    {
        if (branch == target)
        {
            // find head
            auto commit_id = read_string_from_file(".nanogit/.branch_" + target);
            // swap current_branch
            write_string_to_file(".nanogit/.current_branch", target);
            checkout_id(commit_id);
            break;
        }
    }
}

void checkout_new(const std::string branch_name)
{
    // check if branch already exists
    std::ifstream branches_read(".nanogit/.branches");
    std::string result;
    while (std::getline(branches_read, result))
    {
        if (result == branch_name)
        {
            throw std::runtime_error("ERROR : Branch already exists");
        }
    }
    branches_read.close();
    std::ofstream branches;
    branches.open(".nanogit/.branches", std::ios::app);
    branches << branch_name << "\n";
    branches.close();

    // get current branch and its head commit
    auto current_branch = read_string_from_file(".nanogit/.current_branch");
    auto current_id = read_string_from_file(".nanogit/.branch_" + current_branch);

    // create a new branch file and change current_branch to new_branch
    write_string_to_file(".nanogit/.branch_" + branch_name, current_id);
    write_string_to_file(".nanogit/.current_branch", branch_name);
}

void checkout(const std::string target)
{
    if (is_commit_id(target))
    {
        std :: cerr << "entering";
        auto head_branch = return_head_branch(target);
        std :: cerr << head_branch;
        if (head_branch == "DETACHED")
        {
            write_string_to_file(".nanogit/.current_branch", "DETACHED");
            checkout_id(target);
        }
        else
        {
            checkout_branch(head_branch);
        }
    }
    else
    {
        checkout_branch(target);
    }
}