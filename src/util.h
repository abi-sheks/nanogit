#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

void fs_mkdir(const std::string dir)
{
    if (fs::status(dir).type() == fs::file_type::not_found)
    {
        fs::create_directory(dir);
    }
    else
    {
        throw std::runtime_error("already exists");
    }
}

void fs_rm(const std::string filename)
{
    if (!fs::remove(filename))
    {
        throw std::runtime_error("Could not delete");
    }
}

std::string read_string_from_file(const std::string filename)
{
    std::ifstream fp;
    fp.open(filename);
    std::string result;
    std::getline(fp, result);
    fp.close();
    return result;
}
void write_string_to_file(const std::string filename, const std::string str)
{
    std::ofstream fp;
    if (!fp)
    {
        throw std::runtime_error("Files could not be made");
    }
    fp.open(filename);
    fp << str;
    fp.close();
}

bool is_exists(const std::string filename)
{
    // checks whether file exists and is a file
    auto file_status = fs::status(filename).type();
    return file_status != fs::file_type::not_found;
}

void restore_state(const std::string dir)
{
    // expects directory in the form .nanogit/.commit_id
    std::ifstream index(".nanogit/.index");
    std::string tracked;
    while (std::getline(index, tracked))
    {
        auto src = fs::path(std::string(fs::current_path()) + "/" + dir + "/" + tracked);
        auto dest = fs::path(std::string(fs::current_path()) + "/" + tracked);
        fs::copy(src, dest, fs::copy_options::overwrite_existing);
    }
}

bool is_commit_id(std::string str)
{
    // i have no fucking clue why this bug exists trust
    auto new_str = str.substr(0, 40);
    if (new_str.length() != 40)
    {
        return false;
    }
    for (int i = 0; i < 40; i++)
    {
        if (new_str[i] != '5' && new_str[i] != '0' && new_str[i] != 'b')
        {
            return false;
        }
    }
    return true;
}